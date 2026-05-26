# -*- coding: utf-8 -*-
"""实验8 公共模块：基于 ORB / AKAZE 的平面物体跟踪（含几何与时序校验）。"""

from __future__ import annotations

import time
from dataclasses import dataclass
from pathlib import Path
from typing import Literal

import cv2
import numpy as np

ROOT = Path(__file__).resolve().parent
DATA_DIR = ROOT / "data"
TEMPLATE_PATH = DATA_DIR / "template.jpg"
VIDEO_PATH = DATA_DIR / "video.mp4"
REFERENCE_RESULT_PATH = DATA_DIR / "reference_result.png"
OUTPUT_DIR = ROOT / "output"

DetectorName = Literal["orb", "akaze"]


@dataclass
class TrackStats:
    tracked: bool
    good_matches: int = 0
    inliers: int = 0
    inlier_ratio: float = 0.0
    reproj_err: float = 0.0
    detect_ms: float = 0.0
    match_ms: float = 0.0
    reject_reason: str = ""


def ratio_test(knn_matches, ratio: float = 0.7):
    good = []
    for pair in knn_matches:
        if len(pair) < 2:
            continue
        m, n = pair[0], pair[1]
        if m.distance < ratio * n.distance:
            good.append(m)
    return good


def mutual_ratio_matches(des_template, des_frame, matcher, ratio: float = 0.7):
    """双向 ratio test，只保留互最近邻匹配，显著减少误匹配。"""
    knn_tf = matcher.knnMatch(des_template, des_frame, k=2)
    knn_ft = matcher.knnMatch(des_frame, des_template, k=2)
    good_tf = ratio_test(knn_tf, ratio)
    good_ft = ratio_test(knn_ft, ratio)

    ft_map: dict[tuple[int, int], object] = {}
    for m in good_ft:
        ft_map[(m.trainIdx, m.queryIdx)] = m

    mutual = []
    for m in good_tf:
        if (m.queryIdx, m.trainIdx) in ft_map:
            mutual.append(m)
    return mutual


def create_detector(name: DetectorName):
    if name == "orb":
        return (
            cv2.ORB_create(nfeatures=4000, scaleFactor=1.2, nlevels=8, edgeThreshold=15),
            cv2.NORM_HAMMING,
        )
    if name == "akaze":
        return cv2.AKAZE_create(), cv2.NORM_HAMMING
    raise ValueError(f"未知检测器: {name}")


def _quad_area(pts: np.ndarray) -> float:
    return float(cv2.contourArea(pts.reshape(-1, 1, 2).astype(np.float32)))


def _mean_reproj_error(H: np.ndarray, src: np.ndarray, dst: np.ndarray) -> float:
    proj = cv2.perspectiveTransform(src, H)
    diff = proj.reshape(-1, 2) - dst.reshape(-1, 2)
    return float(np.mean(np.linalg.norm(diff, axis=1)))


def validate_quad(
    corners: np.ndarray,
    frame_w: int,
    frame_h: int,
    template_w: int,
    template_h: int,
    prev_corners: np.ndarray | None = None,
    max_corner_jump_ratio: float = 0.12,
) -> tuple[bool, str]:
    pts = corners.reshape(4, 2).astype(np.float32)

    if not cv2.isContourConvex(pts.astype(np.int32)):
        return False, "non_convex"

    margin = -20
    if (
        np.any(pts[:, 0] < margin)
        or np.any(pts[:, 1] < margin)
        or np.any(pts[:, 0] > frame_w + 20)
        or np.any(pts[:, 1] > frame_h + 20)
    ):
        return False, "out_of_frame"

    frame_area = frame_w * frame_h
    area = _quad_area(pts)
    if area < 0.008 * frame_area or area > 0.75 * frame_area:
        return False, "bad_area"

    w_top = np.linalg.norm(pts[1] - pts[0])
    w_bot = np.linalg.norm(pts[2] - pts[3])
    h_left = np.linalg.norm(pts[3] - pts[0])
    h_right = np.linalg.norm(pts[2] - pts[1])
    w_est = (w_top + w_bot) * 0.5
    h_est = (h_left + h_right) * 0.5
    if h_est < 8.0 or w_est < 8.0:
        return False, "too_small"

    template_aspect = template_w / max(template_h, 1)
    aspect = w_est / h_est
    ratio_err = max(aspect / template_aspect, template_aspect / aspect)
    if ratio_err > 2.2:
        return False, "bad_aspect"

    if prev_corners is not None:
        prev = prev_corners.reshape(4, 2)
        jump = np.max(np.linalg.norm(pts - prev, axis=1))
        diag = np.hypot(frame_w, frame_h)
        if jump > max_corner_jump_ratio * diag:
            return False, "jump_too_large"

    return True, ""


class PlanarTracker:
    """模板特征一次提取；逐帧互匹配 + RANSAC 单应性 + 多重校验 + 保守平滑。"""

    def __init__(
        self,
        template_bgr: np.ndarray,
        detector_name: DetectorName = "orb",
        ratio: float = 0.7,
        ransac_thresh: float = 4.0,
        min_good_matches: int = 12,
        min_inliers: int = 12,
        min_inlier_ratio: float = 0.38,
        max_reproj_err: float = 5.0,
        smooth_alpha: float = 0.55,
        max_hold_frames: int = 2,
        process_max_width: int = 960,
        max_corner_jump_ratio: float = 0.14,
    ) -> None:
        if template_bgr is None or template_bgr.size == 0:
            raise ValueError("模板图像无效")

        self.template_bgr = template_bgr
        self.template_gray = cv2.cvtColor(template_bgr, cv2.COLOR_BGR2GRAY)
        self.template_h, self.template_w = self.template_gray.shape[:2]
        self.ratio = ratio
        self.ransac_thresh = ransac_thresh
        self.min_good_matches = min_good_matches
        self.min_inliers = min_inliers
        self.min_inlier_ratio = min_inlier_ratio
        self.max_reproj_err = max_reproj_err
        self.smooth_alpha = smooth_alpha
        self.max_hold_frames = max_hold_frames
        self.process_max_width = process_max_width
        self.max_corner_jump_ratio = max_corner_jump_ratio

        detector, norm = create_detector(detector_name)
        self.detector = detector
        self.matcher = cv2.BFMatcher(norm, crossCheck=False)

        self.template_kp, self.template_des = self.detector.detectAndCompute(
            self.template_gray, None
        )
        if self.template_des is None or len(self.template_kp) < 8:
            raise RuntimeError("模板特征点不足，请更换更清晰、纹理更丰富的模板")

        self.template_corners = np.float32(
            [[0, 0], [self.template_w, 0], [self.template_w, self.template_h], [0, self.template_h]]
        ).reshape(-1, 1, 2)

        self.confirmed_corners: np.ndarray | None = None
        self.missed_frames = 0

    def _prepare_frame(self, frame_bgr: np.ndarray):
        h, w = frame_bgr.shape[:2]
        scale = 1.0
        if self.process_max_width > 0 and w > self.process_max_width:
            scale = self.process_max_width / float(w)
            new_w = int(w * scale)
            new_h = int(h * scale)
            work = cv2.resize(frame_bgr, (new_w, new_h), interpolation=cv2.INTER_AREA)
        else:
            work = frame_bgr
        return work, scale, w, h

    def _estimate_corners(
        self,
        frame_bgr: np.ndarray,
        stats: TrackStats,
    ) -> tuple[np.ndarray | None, str]:
        work, scale, frame_w, frame_h = self._prepare_frame(frame_bgr)
        gray = cv2.cvtColor(work, cv2.COLOR_BGR2GRAY)

        t0 = time.perf_counter()
        kp_frame, des_frame = self.detector.detectAndCompute(gray, None)
        stats.detect_ms = (time.perf_counter() - t0) * 1000.0

        if des_frame is None or len(kp_frame) < 8:
            return None, "no_features"

        t1 = time.perf_counter()
        good = mutual_ratio_matches(self.template_des, des_frame, self.matcher, self.ratio)
        stats.match_ms = (time.perf_counter() - t1) * 1000.0
        stats.good_matches = len(good)

        if len(good) < self.min_good_matches:
            return None, "few_matches"

        pts_template = np.float32([self.template_kp[m.queryIdx].pt for m in good]).reshape(-1, 1, 2)
        pts_frame = np.float32([kp_frame[m.trainIdx].pt for m in good]).reshape(-1, 1, 2)

        H, mask = cv2.findHomography(
            pts_template,
            pts_frame,
            cv2.RANSAC,
            self.ransac_thresh,
            maxIters=3000,
            confidence=0.995,
        )
        if H is None or mask is None:
            return None, "no_homography"

        inlier_idx = [i for i, m in enumerate(mask.ravel()) if m]
        stats.inliers = len(inlier_idx)
        stats.inlier_ratio = stats.inliers / max(len(good), 1)

        if stats.inliers < self.min_inliers or stats.inlier_ratio < self.min_inlier_ratio:
            return None, "few_inliers"

        inlier_template = pts_template[inlier_idx]
        inlier_frame = pts_frame[inlier_idx]
        H_refined, _ = cv2.findHomography(inlier_template, inlier_frame, 0)
        if H_refined is None:
            H_refined = H

        stats.reproj_err = _mean_reproj_error(H_refined, inlier_template, inlier_frame)
        if stats.reproj_err > self.max_reproj_err:
            return None, "high_reproj"

        corners = cv2.perspectiveTransform(self.template_corners, H_refined)
        if scale != 1.0:
            corners /= scale

        ok, reason = validate_quad(
            corners,
            frame_w,
            frame_h,
            self.template_w,
            self.template_h,
            prev_corners=self.confirmed_corners,
            max_corner_jump_ratio=self.max_corner_jump_ratio,
        )
        if not ok:
            return None, reason

        return corners, ""

    def _accept_corners(self, corners: np.ndarray | None, reject_reason: str) -> np.ndarray | None:
        if corners is not None:
            if self.confirmed_corners is None:
                self.confirmed_corners = corners.copy()
            else:
                self.confirmed_corners = (
                    self.smooth_alpha * corners + (1.0 - self.smooth_alpha) * self.confirmed_corners
                )
            self.missed_frames = 0
            return self.confirmed_corners

        self.missed_frames += 1
        if self.confirmed_corners is not None and self.missed_frames <= self.max_hold_frames:
            return self.confirmed_corners

        self.confirmed_corners = None
        return None

    def track(self, frame_bgr: np.ndarray) -> tuple[np.ndarray | None, TrackStats]:
        stats = TrackStats(tracked=False)
        corners, reason = self._estimate_corners(frame_bgr, stats)
        stats.reject_reason = reason
        display_corners = self._accept_corners(corners, reason)
        stats.tracked = display_corners is not None and corners is not None
        return display_corners, stats

    @staticmethod
    def draw_wireframe(
        frame_bgr: np.ndarray,
        corners: np.ndarray | None,
        color: tuple[int, int, int] = (255, 0, 0),
        thickness: int = 3,
    ) -> np.ndarray:
        out = frame_bgr.copy()
        if corners is None:
            return out
        pts = np.int32(corners.reshape(-1, 2))
        cv2.polylines(out, [pts], isClosed=True, color=color, thickness=thickness, lineType=cv2.LINE_AA)
        return out
