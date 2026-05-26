# Vendored from https://github.com/cvg/LightGlue (lightglue/superpoint.py)
# SuperPoint pretrained weights: LightGlue release superpoint_v1.pth

from __future__ import annotations

import torch
from kornia.color import rgb_to_grayscale
from torch import nn

from .utils_min import Extractor


def simple_nms(scores, nms_radius: int):
    assert nms_radius >= 0

    def max_pool(x):
        return torch.nn.functional.max_pool2d(
            x, kernel_size=nms_radius * 2 + 1, stride=1, padding=nms_radius
        )

    zeros = torch.zeros_like(scores)
    max_mask = scores == max_pool(scores)
    for _ in range(2):
        supp_mask = max_pool(max_mask.float()) > 0
        supp_scores = torch.where(supp_mask, zeros, scores)
        new_max_mask = supp_scores == max_pool(supp_scores)
        max_mask = max_mask | (new_max_mask & (~supp_mask))
    return torch.where(max_mask, scores, zeros)


def top_k_keypoints(keypoints, scores, k):
    if k >= len(keypoints):
        return keypoints, scores
    scores, indices = torch.topk(scores, k, dim=0, sorted=True)
    return keypoints[indices], scores


def sample_descriptors(keypoints, descriptors, s: int = 8):
    b, c, h, w = descriptors.shape
    keypoints = keypoints - s / 2 + 0.5
    keypoints /= torch.tensor(
        [(w * s - s / 2 - 0.5), (h * s - s / 2 - 0.5)],
    ).to(keypoints)[None]
    keypoints = keypoints * 2 - 1
    args = {"align_corners": True} if torch.__version__ >= "1.3" else {}
    descriptors = torch.nn.functional.grid_sample(
        descriptors, keypoints.view(b, 1, -1, 2), mode="bilinear", **args
    )
    descriptors = torch.nn.functional.normalize(
        descriptors.reshape(b, c, -1), p=2, dim=1
    )
    return descriptors


class SuperPoint(Extractor):
    default_conf = {
        "descriptor_dim": 256,
        "nms_radius": 4,
        "max_num_keypoints": None,
        "detection_threshold": 0.0005,
        "remove_borders": 4,
    }
    preprocess_conf = {"resize": 1024}
    required_data_keys = ["image"]

    def __init__(self, **conf):
        super().__init__(**conf)
        self.relu = nn.ReLU(inplace=True)
        self.pool = nn.MaxPool2d(kernel_size=2, stride=2)
        c1, c2, c3, c4, c5 = 64, 64, 128, 128, 256

        self.conv1a = nn.Conv2d(1, c1, kernel_size=3, stride=1, padding=1)
        self.conv1b = nn.Conv2d(c1, c1, kernel_size=3, stride=1, padding=1)
        self.conv2a = nn.Conv2d(c1, c2, kernel_size=3, stride=1, padding=1)
        self.conv2b = nn.Conv2d(c2, c2, kernel_size=3, stride=1, padding=1)
        self.conv3a = nn.Conv2d(c2, c3, kernel_size=3, stride=1, padding=1)
        self.conv3b = nn.Conv2d(c3, c3, kernel_size=3, stride=1, padding=1)
        self.conv4a = nn.Conv2d(c3, c4, kernel_size=3, stride=1, padding=1)
        self.conv4b = nn.Conv2d(c4, c4, kernel_size=3, stride=1, padding=1)
        self.convPa = nn.Conv2d(c4, c5, kernel_size=3, stride=1, padding=1)
        self.convPb = nn.Conv2d(c5, 65, kernel_size=1, stride=1, padding=0)
        self.convDa = nn.Conv2d(c4, c5, kernel_size=3, stride=1, padding=1)
        self.convDb = nn.Conv2d(
            c5, self.conf.descriptor_dim, kernel_size=1, stride=1, padding=0
        )

        url = "https://github.com/cvg/LightGlue/releases/download/v0.1_arxiv/superpoint_v1.pth"
        self.load_state_dict(torch.hub.load_state_dict_from_url(url))

    def forward(self, data: dict) -> dict:
        image = data["image"]
        if image.shape[1] == 3:
            image = rgb_to_grayscale(image)

        x = self.relu(self.conv1a(image))
        x = self.relu(self.conv1b(x))
        x = self.pool(x)
        x = self.relu(self.conv2a(x))
        x = self.relu(self.conv2b(x))
        x = self.pool(x)
        x = self.relu(self.conv3a(x))
        x = self.relu(self.conv3b(x))
        x = self.pool(x)
        x = self.relu(self.conv4a(x))
        x = self.relu(self.conv4b(x))

        cPa = self.relu(self.convPa(x))
        scores = self.convPb(cPa)
        scores = torch.nn.functional.softmax(scores, 1)[:, :-1]
        b, _, h, w = scores.shape
        scores = scores.permute(0, 2, 3, 1).reshape(b, h, w, 8, 8)
        scores = scores.permute(0, 1, 3, 2, 4).reshape(b, h * 8, w * 8)
        scores = simple_nms(scores, self.conf.nms_radius)

        if self.conf.remove_borders:
            pad = self.conf.remove_borders
            scores[:, :pad] = -1
            scores[:, :, :pad] = -1
            scores[:, -pad:] = -1
            scores[:, :, -pad:] = -1

        best_kp = torch.where(scores > self.conf.detection_threshold)
        scores_flat = scores[best_kp]
        keypoints = [
            torch.stack(best_kp[1:3], dim=-1)[best_kp[0] == i] for i in range(b)
        ]
        scores_list = [scores_flat[best_kp[0] == i] for i in range(b)]

        if self.conf.max_num_keypoints is not None:
            keypoints, scores_list = zip(
                *[
                    top_k_keypoints(k, s, self.conf.max_num_keypoints)
                    for k, s in zip(keypoints, scores_list)
                ]
            )
            keypoints, scores_list = list(keypoints), list(scores_list)

        keypoints = [torch.flip(k, [1]).float() for k in keypoints]

        cDa = self.relu(self.convDa(x))
        descriptors = self.convDb(cDa)
        descriptors = torch.nn.functional.normalize(descriptors, p=2, dim=1)
        descriptors = [
            sample_descriptors(k[None], d[None], 8)[0]
            for k, d in zip(keypoints, descriptors)
        ]

        return {
            "keypoints": torch.stack(keypoints, 0),
            "keypoint_scores": torch.stack(scores_list, 0),
            "descriptors": torch.stack(descriptors, 0).transpose(-1, -2).contiguous(),
        }
