# -*- coding: utf-8 -*-
"""实验7 公共工具：特征提取、NN/LightGlue 匹配、指标与可视化。"""

from __future__ import annotations

import json
import time
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Literal

import cv2
import numpy as np

ROOT = Path(__file__).resolve().parent
EXP6 = ROOT.parent / "实验6"
REF_PATH = ROOT.parent / "mumu.jpg"
META_PATH = EXP6 / "data" / "sweep_meta.json"
RANDOM_IMG = EXP6 / "images" / "mumu_random.jpg"

FeatureName = Literal["superpoint", "disk", "aliked", "sift"]
MatcherName = Literal["nn", "lightglue"]

FEATURE_ORDER: tuple[FeatureName, ...] = ("superpoint", "disk", "aliked", "sift")
MATCHER_ORDER: tuple[MatcherName, ...] = ("nn", "lightglue")

VIS_ROT_ANGLES = {0, 30, 60}
VIS_SCALE_PCTS = {60, 100, 130}


@dataclass
class MatchMetrics:
    feature: str
    matcher: str
    sweep_type: str
    param_value: float
    num_kp1: int
    num_kp2: int
    num_matches: int
    num_inliers: int
    inlier_ratio: float
    mean_reproj_err: float
    t_extract_ms: float
    t_match_ms: float


def load_meta() -> dict:
    if not META_PATH.exists():
        raise FileNotFoundError(
            f"找不到 {META_PATH.resolve()}，请先在实验6目录运行: python 实验6-2-0_sweep.py"
        )
    return json.loads(META_PATH.read_text(encoding="utf-8"))


def M_to_H(M: list[list[float]]) -> np.ndarray:
    M_arr = np.asarray(M, dtype=np.float64)
    H = np.eye(3, dtype=np.float64)
    H[:2, :] = M_arr
    return H


def ransac_inliers(
    pts1: np.ndarray,
    pts2: np.ndarray,
    matches: list[cv2.DMatch],
    thresh: float = 5.0,
) -> tuple[list[cv2.DMatch], np.ndarray | None]:
    if len(matches) < 4:
        return [], None
    p1 = np.float32([pts1[m.queryIdx] for m in matches]).reshape(-1, 1, 2)
    p2 = np.float32([pts2[m.trainIdx] for m in matches]).reshape(-1, 1, 2)
    _, mask = cv2.findHomography(p1, p2, cv2.RANSAC, thresh)
    if mask is None:
        return [], None
    inliers = [matches[i] for i in range(len(matches)) if mask[i]]
    return inliers, mask


def mean_reproj_error(
    pts1: np.ndarray,
    pts2: np.ndarray,
    matches: list[cv2.DMatch],
    H_gt: np.ndarray,
) -> float:
    if not matches:
        return float("nan")
    errors = []
    for m in matches:
        p1 = np.array([pts1[m.queryIdx][0], pts1[m.queryIdx][1], 1.0])
        p2 = pts2[m.trainIdx]
        p1_w = H_gt @ p1
        p1_w /= p1_w[2]
        errors.append(float(np.linalg.norm(p2 - p1_w[:2])))
    return float(np.mean(errors))


def kps_to_cv2(pts: np.ndarray) -> list[cv2.KeyPoint]:
    return [cv2.KeyPoint(float(x), float(y), 8) for x, y in pts]


def draw_matches(
    img1: np.ndarray,
    pts1: np.ndarray,
    img2: np.ndarray,
    pts2: np.ndarray,
    matches: list[cv2.DMatch],
    out_path: Path,
) -> None:
    vis = cv2.drawMatches(
        img1,
        kps_to_cv2(pts1),
        img2,
        kps_to_cv2(pts2),
        matches,
        None,
        matchColor=(0, 255, 0),
        flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS,
    )
    out_path.parent.mkdir(parents=True, exist_ok=True)
    cv2.imwrite(str(out_path), vis)


def should_visualize(sweep_type: str, param_value: float) -> bool:
    if sweep_type == "pair":
        return True
    if sweep_type == "rotation":
        return int(param_value) in VIS_ROT_ANGLES
    pct = int(round(param_value * 100))
    return pct in VIS_SCALE_PCTS


def _ensure_exp6_vendor_path() -> None:
    import sys

    exp6 = str(EXP6)
    if exp6 not in sys.path:
        sys.path.insert(0, exp6)


def detect_backend() -> str:
    """优先 kornia；SuperPoint 在 0.8+ 可回退到实验6 vendor。"""
    from packaging import version as pkg_version

    try:
        import kornia
        import kornia.feature as KF

        if pkg_version.parse(kornia.__version__) < pkg_version.parse("0.7.3"):
            raise ImportError(
                f"当前 kornia={kornia.__version__}，实验7 需要 >=0.7.3。\n"
                "  pip install -U 'kornia>=0.8'"
            )
        for name in ("LightGlue", "DISK", "SIFTFeature"):
            if not hasattr(KF, name):
                raise ImportError(f"kornia.feature 缺少 {name}")
        if not hasattr(KF, "SuperPoint"):
            _ensure_exp6_vendor_path()
            from vendor.superpoint import SuperPoint  # noqa: F401
        if not hasattr(KF, "ALIKED"):
            raise ImportError(
                "kornia 无 ALIKED，请升级: pip install -U 'kornia>=0.8'"
            )
        return "kornia"
    except ImportError:
        pass

    try:
        import lightglue  # noqa: F401

        return "lightglue"
    except ImportError as e:
        raise ImportError(
            "未检测到可用的 LightGlue 后端。\n"
            "推荐: 运行 实验7/创建视觉实验环境.ps1\n"
            "或: pip install -U 'kornia>=0.8' 与 CPU 版 torch"
        ) from e


def check_backend() -> str:
    return detect_backend()


# 兼容旧脚本名
check_lightglue_import = check_backend


class LightGluePipeline:
    """同一特征提取器下，对比 mutual-NN 与 LightGlue 匹配（默认走 kornia）。"""

    def __init__(self, feature: FeatureName, device: str, max_num_keypoints: int = 2048):
        import torch

        self.backend = detect_backend()
        self.torch = torch
        self.device = torch.device(device)
        self.feature = feature
        self.max_kp = max_num_keypoints

        if self.backend == "kornia":
            self._init_kornia()
        else:
            self._init_lightglue_pkg()

    def _init_kornia(self) -> None:
        import kornia.feature as KF
        from kornia.color import rgb_to_grayscale
        from kornia.constants import pi
        from kornia.feature.laf import get_laf_center, get_laf_orientation, get_laf_scale
        from kornia.geometry import deg2rad

        self.KF = KF
        self.rgb_to_grayscale = rgb_to_grayscale
        self.pi = pi
        self.get_laf_center = get_laf_center
        self.get_laf_orientation = get_laf_orientation
        self.get_laf_scale = get_laf_scale
        self.deg2rad = deg2rad

        self.matcher = KF.LightGlue(self.feature).eval().to(self.device)
        self.sp_backend = "kornia"

        if self.feature == "superpoint":
            if hasattr(KF, "SuperPoint"):
                self.extractor = KF.SuperPoint(max_num_keypoints=self.max_kp).eval().to(
                    self.device
                )
            else:
                _ensure_exp6_vendor_path()
                from vendor.superpoint import SuperPoint

                self.sp_backend = "vendor"
                self.extractor = SuperPoint(max_num_keypoints=self.max_kp).to(
                    self.device
                ).eval()
        elif self.feature == "disk":
            self.extractor = KF.DISK.from_pretrained("depth", device=self.device)
        elif self.feature == "aliked":
            self.extractor = KF.ALIKED.from_pretrained(
                "aliked-n16",
                max_num_keypoints=self.max_kp,
                device=self.device,
            ).eval()
        elif self.feature == "sift":
            self.extractor = KF.SIFTFeature(
                num_features=self.max_kp, device=self.device
            ).eval().to(self.device)
        else:
            raise ValueError(self.feature)

    def _init_lightglue_pkg(self) -> None:
        from lightglue import ALIKED, DISK, LightGlue, SIFT, SuperPoint
        from lightglue.utils import rbd

        self.rbd = rbd
        cls_map = {
            "superpoint": SuperPoint,
            "disk": DISK,
            "aliked": ALIKED,
            "sift": SIFT,
        }
        self.extractor = (
            cls_map[self.feature](max_num_keypoints=self.max_kp).eval().to(self.device)
        )
        self.matcher = LightGlue(features=self.feature).eval().to(self.device)

    def _bgr_to_rgb_batch(self, img_bgr: np.ndarray):
        rgb = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB)
        t = self.torch.from_numpy(rgb).float().permute(2, 0, 1).unsqueeze(0) / 255.0
        return t.to(self.device)

    def _image_size_tensor(self, img_bgr: np.ndarray):
        h, w = img_bgr.shape[:2]
        return self.torch.tensor([[w, h]], device=self.device, dtype=self.torch.float32)

    def _extract_kornia(self, img_bgr: np.ndarray) -> dict:
        h, w = img_bgr.shape[:2]
        image_size = self._image_size_tensor(img_bgr)

        with self.torch.inference_mode():
            if self.feature == "superpoint":
                gray = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2GRAY)
                t = self.torch.from_numpy(gray).float().unsqueeze(0).unsqueeze(0) / 255.0
                t = t.to(self.device)
                if getattr(self, "sp_backend", "kornia") == "vendor":
                    out = self.extractor({"image": t})
                else:
                    out = self.extractor(t)
                kps = out["keypoints"][0]
                desc = out["descriptors"][0]
            elif self.feature == "disk":
                t = self._bgr_to_rgb_batch(img_bgr)
                feat = self.extractor(
                    t, n=self.max_kp, pad_if_not_divisible=True
                )[0]
                kps = feat.keypoints
                desc = feat.descriptors
            elif self.feature == "aliked":
                t = self._bgr_to_rgb_batch(img_bgr)
                feat = self.extractor(t)[0]
                kps = feat.keypoints
                desc = feat.descriptors
            else:  # sift
                t = self.rgb_to_grayscale(self._bgr_to_rgb_batch(img_bgr))
                lafs, _, desc = self.extractor(t)
                kps = self.get_laf_center(lafs)[0]
                ori = self.deg2rad(self.get_laf_orientation(lafs).reshape(1, -1))
                ori = ori.clone()
                ori[ori < 0] += 2.0 * self.pi
                pack = {
                    "keypoints": kps.unsqueeze(0),
                    "descriptors": desc,
                    "image_size": image_size,
                    "scales": self.get_laf_scale(lafs).reshape(1, -1),
                    "oris": ori,
                    "lafs": lafs,
                }
                return pack

        return {
            "keypoints": kps.unsqueeze(0),
            "descriptors": desc.unsqueeze(0) if desc.dim() == 2 else desc,
            "image_size": image_size,
        }

    def _extract_lg_pkg(self, img_bgr: np.ndarray) -> dict:
        rgb = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB)
        t = self.torch.from_numpy(rgb).float() / 255.0
        t = t.permute(2, 0, 1).to(self.device)
        with self.torch.inference_mode():
            return self.extractor.extract(t)

    def extract_one(self, img_bgr: np.ndarray) -> dict:
        if self.backend == "kornia":
            return self._extract_kornia(img_bgr)
        return self._extract_lg_pkg(img_bgr)

    def extract_pair(
        self, img_ref_bgr: np.ndarray, img_warp_bgr: np.ndarray
    ) -> tuple[dict, dict, float]:
        t0 = time.perf_counter()
        feats0 = self.extract_one(img_ref_bgr)
        feats1 = self.extract_one(img_warp_bgr)
        t_ms = (time.perf_counter() - t0) * 1000
        return feats0, feats1, t_ms

    def _squeeze_feats(self, feats: dict) -> dict:
        if self.backend == "lightglue":
            from lightglue.utils import rbd

            return rbd(feats)
        out: dict = {}
        for k, v in feats.items():
            if (
                isinstance(v, self.torch.Tensor)
                and v.dim() >= 2
                and v.shape[0] == 1
                and k in ("keypoints", "descriptors", "scales", "oris")
            ):
                out[k] = v.squeeze(0)
            else:
                out[k] = v
        return out

    def match_nn(self, feats0: dict, feats1: dict) -> tuple[np.ndarray, np.ndarray, list[cv2.DMatch]]:
        f0 = self._squeeze_feats(feats0)
        f1 = self._squeeze_feats(feats1)
        d0 = f0["descriptors"].float()
        d1 = f1["descriptors"].float()
        if d0.dim() == 3:
            d0 = d0.squeeze(0)
        if d1.dim() == 3:
            d1 = d1.squeeze(0)

        sim = d0 @ d1.T
        nn01 = sim.argmax(dim=1)
        nn10 = sim.argmax(dim=0)
        mutual = []
        for i in range(sim.shape[0]):
            j = int(nn01[i].item())
            if int(nn10[j].item()) == i:
                mutual.append(cv2.DMatch(_queryIdx=i, _trainIdx=j, _distance=0.0))

        pts0 = f0["keypoints"].detach().cpu().numpy().astype(np.float32)
        pts1 = f1["keypoints"].detach().cpu().numpy().astype(np.float32)
        return pts0, pts1, mutual

    def match_lightglue(
        self, feats0: dict, feats1: dict
    ) -> tuple[np.ndarray, np.ndarray, list[cv2.DMatch]]:
        with self.torch.inference_mode():
            out = self.matcher({"image0": feats0, "image1": feats1})

        if self.backend == "kornia":
            idx = out["matches"][0].detach().cpu().numpy()
            f0 = self._squeeze_feats(feats0)
            f1 = self._squeeze_feats(feats1)
        else:
            from lightglue.utils import rbd

            f0 = rbd(feats0)
            f1 = rbd(feats1)
            out = rbd(out)
            idx = out["matches"].cpu().numpy()

        pts0 = f0["keypoints"].detach().cpu().numpy().astype(np.float32)
        pts1 = f1["keypoints"].detach().cpu().numpy().astype(np.float32)
        matches = [
            cv2.DMatch(_queryIdx=int(i), _trainIdx=int(j), _distance=0.0)
            for i, j in idx
        ]
        return pts0, pts1, matches

    def evaluate(
        self,
        feats0: dict,
        feats1: dict,
        matcher: MatcherName,
        img_ref_bgr: np.ndarray,
        img_warp_bgr: np.ndarray,
        t_extract_ms: float,
        H_gt: np.ndarray | None = None,
        sweep_type: str = "pair",
        param_value: float = 0.0,
        fig_dir: Path | None = None,
        tag: str = "demo",
    ) -> MatchMetrics:
        t1 = time.perf_counter()
        if matcher == "nn":
            pts0, pts1, matches = self.match_nn(feats0, feats1)
        else:
            pts0, pts1, matches = self.match_lightglue(feats0, feats1)
        t_match = (time.perf_counter() - t1) * 1000

        inliers, _ = ransac_inliers(pts0, pts1, matches)
        inlier_ratio = (len(inliers) / len(matches)) if matches else 0.0
        reproj = (
            mean_reproj_error(pts0, pts1, inliers, H_gt)
            if H_gt is not None
            else float("nan")
        )

        if fig_dir is not None and should_visualize(sweep_type, param_value):
            base = fig_dir / f"{tag}_{self.feature}_{matcher}"
            draw_matches(img_ref_bgr, pts0, img_warp_bgr, pts1, matches, Path(str(base) + "_matches.png"))
            draw_matches(img_ref_bgr, pts0, img_warp_bgr, pts1, inliers, Path(str(base) + "_ransac.png"))

        return MatchMetrics(
            feature=self.feature,
            matcher=matcher,
            sweep_type=sweep_type,
            param_value=param_value,
            num_kp1=len(pts0),
            num_kp2=len(pts1),
            num_matches=len(matches),
            num_inliers=len(inliers),
            inlier_ratio=inlier_ratio,
            mean_reproj_err=reproj,
            t_extract_ms=t_extract_ms,
            t_match_ms=t_match,
        )

    def run_pair(
        self,
        img_ref_bgr: np.ndarray,
        img_warp_bgr: np.ndarray,
        matcher: MatcherName,
        H_gt: np.ndarray | None = None,
        sweep_type: str = "pair",
        param_value: float = 0.0,
        fig_dir: Path | None = None,
        tag: str = "demo",
    ) -> MatchMetrics:
        feats0, feats1, t_extract = self.extract_pair(img_ref_bgr, img_warp_bgr)
        return self.evaluate(
            feats0,
            feats1,
            matcher,
            img_ref_bgr,
            img_warp_bgr,
            t_extract,
            H_gt=H_gt,
            sweep_type=sweep_type,
            param_value=param_value,
            fig_dir=fig_dir,
            tag=tag,
        )


def metrics_to_rows(rows: list[MatchMetrics], csv_path: Path) -> None:
    import csv

    csv_path.parent.mkdir(parents=True, exist_ok=True)
    fields = list(MatchMetrics.__dataclass_fields__.keys())
    with csv_path.open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fields)
        w.writeheader()
        for r in rows:
            w.writerow(asdict(r))


def plot_sweep_curves(rows: list[MatchMetrics], fig_dir: Path) -> None:
    import matplotlib.pyplot as plt

    fig_dir.mkdir(parents=True, exist_ok=True)
    colors = {"nn": "C0", "lightglue": "C1"}

    for feature in FEATURE_ORDER:
        for sweep_type, xlabel, fname in (
            ("rotation", "rotation angle (deg)", f"curve_{feature}_rotation.png"),
            ("scale", "scale factor", f"curve_{feature}_scale.png"),
        ):
            fig, axes = plt.subplots(1, 2, figsize=(10, 4))
            for matcher in MATCHER_ORDER:
                sub = [
                    r
                    for r in rows
                    if r.feature == feature
                    and r.matcher == matcher
                    and r.sweep_type == sweep_type
                ]
                sub.sort(key=lambda r: r.param_value)
                if not sub:
                    continue
                xs = [r.param_value for r in sub]
                axes[0].plot(
                    xs,
                    [r.num_inliers for r in sub],
                    "-o",
                    label=matcher,
                    color=colors[matcher],
                )
                axes[1].plot(
                    xs,
                    [r.inlier_ratio for r in sub],
                    "-o",
                    label=matcher,
                    color=colors[matcher],
                )
            axes[0].set_xlabel(xlabel)
            axes[0].set_ylabel("RANSAC inliers")
            axes[0].set_title(f"{feature} / {sweep_type}")
            axes[1].set_xlabel(xlabel)
            axes[1].set_ylabel("inlier ratio")
            for ax in axes:
                ax.legend()
                ax.grid(True, alpha=0.3)
            fig.tight_layout()
            fig.savefig(fig_dir / fname, dpi=150)
            plt.close(fig)

    # 汇总：固定旋转 30° / 尺度 1.0 时各特征 NN vs LightGlue 内点数
    fig, ax = plt.subplots(figsize=(8, 4))
    bench = []
    for feature in FEATURE_ORDER:
        for matcher in MATCHER_ORDER:
            rot = next(
                (
                    r
                    for r in rows
                    if r.feature == feature
                    and r.matcher == matcher
                    and r.sweep_type == "rotation"
                    and abs(r.param_value - 30.0) < 0.1
                ),
                None,
            )
            if rot:
                bench.append((f"{feature}\n{matcher}", rot.num_inliers))
    if bench:
        labels, vals = zip(*bench)
        ax.bar(labels, vals, color=["C0" if "nn" in lb else "C1" for lb in labels])
        ax.set_ylabel("inliers @ 30° rotation")
        ax.tick_params(axis="x", labelsize=8)
        fig.tight_layout()
        fig.savefig(fig_dir / "summary_inliers_rot30.png", dpi=150)
        plt.close(fig)
