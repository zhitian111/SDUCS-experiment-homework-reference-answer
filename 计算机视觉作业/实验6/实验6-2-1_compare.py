# -*- coding: utf-8 -*-
"""实验6.2：SIFT vs SuperPoint 在旋转/尺度 sweep 上的匹配对比。

依赖：opencv-contrib-python, torch, kornia, matplotlib, numpy
需先运行：python 实验6-2-0_sweep.py
"""

from __future__ import annotations

import csv
import json
import sys
import time
from dataclasses import asdict, dataclass
from pathlib import Path

import cv2
import matplotlib.pyplot as plt
import numpy as np

ROOT = Path(__file__).resolve().parent
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

REF_PATH = ROOT / ".." / "mumu.jpg"
META_PATH = ROOT / "data" / "sweep_meta.json"
FIG_DIR = ROOT / "figures" / "e62"
RESULT_DIR = ROOT / "results"
CSV_PATH = RESULT_DIR / "e62_metrics.csv"

# 仅为控制输出图数量（指标仍对全部 sweep 计算）
VIS_ROT_ANGLES = {0, 30, 60}
VIS_SCALE_PCTS = {60, 100, 130}


@dataclass
class MatchResult:
    method: str
    sweep_type: str
    param_value: float
    num_kp1: int
    num_kp2: int
    num_raw: int
    num_good: int
    num_inliers: int
    inlier_ratio: float
    mean_reproj_err: float
    t_detect_ms: float
    t_match_ms: float


def load_meta() -> dict:
    if not META_PATH.exists():
        raise FileNotFoundError(
            f"找不到 {META_PATH.resolve()}，请先运行: python 实验6-2-0_sweep.py"
        )
    return json.loads(META_PATH.read_text(encoding="utf-8"))


def M_to_H(M: list[list[float]]) -> np.ndarray:
    M = np.asarray(M, dtype=np.float64)
    H = np.eye(3, dtype=np.float64)
    H[:2, :] = M
    return H


def ratio_test(knn_matches, ratio: float = 0.75) -> list[cv2.DMatch]:
    good = []
    for pair in knn_matches:
        if len(pair) < 2:
            continue
        m, n = pair[0], pair[1]
        if m.distance < ratio * n.distance:
            good.append(m)
    return good


def mutual_nn_match(d1: np.ndarray, d2: np.ndarray) -> list[cv2.DMatch]:
    if len(d1) == 0 or len(d2) == 0:
        return []
    matcher = cv2.BFMatcher(cv2.NORM_L2)
    fwd = matcher.match(d1, d2)
    bwd = matcher.match(d2, d1)
    backward = {m.queryIdx: m.trainIdx for m in bwd}
    mutual = []
    for m in fwd:
        q, t = m.queryIdx, m.trainIdx
        if backward.get(t) == q:
            mutual.append(cv2.DMatch(_queryIdx=q, _trainIdx=t, _distance=m.distance))
    return mutual


def ransac_inliers(
    pts1: np.ndarray, pts2: np.ndarray, matches: list[cv2.DMatch], thresh: float = 5.0
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


def draw_and_save(
    img1: np.ndarray,
    pts1: np.ndarray,
    img2: np.ndarray,
    pts2: np.ndarray,
    matches: list[cv2.DMatch],
    out_path: Path,
) -> None:
    kp1 = kps_to_cv2(pts1)
    kp2 = kps_to_cv2(pts2)
    vis = cv2.drawMatches(
        img1,
        kp1,
        img2,
        kp2,
        matches,
        None,
        matchColor=(0, 255, 0),
        flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS,
    )
    out_path.parent.mkdir(parents=True, exist_ok=True)
    cv2.imwrite(str(out_path), vis)


def run_sift(img1: np.ndarray, img2: np.ndarray) -> tuple[np.ndarray, np.ndarray, list[cv2.DMatch], float, float]:
    g1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
    g2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
    sift = cv2.SIFT_create(nfeatures=3000)

    t0 = time.perf_counter()
    kp1, des1 = sift.detectAndCompute(g1, None)
    kp2, des2 = sift.detectAndCompute(g2, None)
    t_detect = (time.perf_counter() - t0) * 1000

    pts1 = np.array([k.pt for k in kp1], dtype=np.float32)
    pts2 = np.array([k.pt for k in kp2], dtype=np.float32)

    t1 = time.perf_counter()
    matcher = cv2.BFMatcher(cv2.NORM_L2)
    knn = matcher.knnMatch(des1, des2, k=2)
    good = ratio_test(knn, 0.75)
    t_match = (time.perf_counter() - t1) * 1000
    return pts1, pts2, good, t_detect, t_match


def load_superpoint_class():
    """优先 kornia（若存在）；否则使用 vendor 内 LightGlue SuperPoint 实现。"""
    try:
        from kornia.feature import SuperPoint as KorniaSuperPoint

        return KorniaSuperPoint, "kornia"
    except ImportError:
        pass

    from vendor.superpoint import SuperPoint as LightGlueSuperPoint

    return LightGlueSuperPoint, "lightglue"


class SuperPointExtractor:
    def __init__(self, device: str = "cpu"):
        import torch

        SuperPoint, self.backend = load_superpoint_class()
        self.torch = torch
        self.device = torch.device(device)
        self.model = SuperPoint(max_num_keypoints=2048).to(self.device).eval()

    def __call__(self, img_bgr: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
        gray = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2GRAY)
        t = self.torch.from_numpy(gray).float() / 255.0
        t = t.unsqueeze(0).unsqueeze(0).to(self.device)
        with self.torch.inference_mode():
            if self.backend == "kornia":
                out = self.model(t)
            else:
                out = self.model({"image": t})
        kps = out["keypoints"][0].detach().cpu().numpy()
        desc = out["descriptors"][0].detach().cpu().numpy()
        return kps.astype(np.float32), desc.astype(np.float32)


def run_superpoint(
    sp: SuperPointExtractor, img1: np.ndarray, img2: np.ndarray
) -> tuple[np.ndarray, np.ndarray, list[cv2.DMatch], float, float]:
    t0 = time.perf_counter()
    pts1, des1 = sp(img1)
    pts2, des2 = sp(img2)
    t_detect = (time.perf_counter() - t0) * 1000

    t1 = time.perf_counter()
    good = mutual_nn_match(des1, des2)
    t_match = (time.perf_counter() - t1) * 1000
    return pts1, pts2, good, t_detect, t_match


def should_visualize(sweep_type: str, param_value: float) -> bool:
    if sweep_type == "rotation":
        return int(param_value) in VIS_ROT_ANGLES
    pct = int(round(param_value * 100))
    return pct in VIS_SCALE_PCTS


def evaluate_pair(
    method: str,
    sweep_type: str,
    param_value: float,
    img_ref: np.ndarray,
    img_warp: np.ndarray,
    H_gt: np.ndarray,
    sp: SuperPointExtractor | None,
    tag: str,
) -> MatchResult:
    if method == "SIFT":
        pts1, pts2, good, t_det, t_match = run_sift(img_ref, img_warp)
    else:
        assert sp is not None
        pts1, pts2, good, t_det, t_match = run_superpoint(sp, img_ref, img_warp)

    inliers, _ = ransac_inliers(pts1, pts2, good)
    inlier_ratio = (len(inliers) / len(good)) if good else 0.0
    reproj = mean_reproj_error(pts1, pts2, inliers, H_gt)

    if should_visualize(sweep_type, param_value):
        base = FIG_DIR / f"{tag}_{method}"
        draw_and_save(img_ref, pts1, img_warp, pts2, good, Path(str(base) + "_matches.png"))
        draw_and_save(img_ref, pts1, img_warp, pts2, inliers, Path(str(base) + "_ransac.png"))

    return MatchResult(
        method=method,
        sweep_type=sweep_type,
        param_value=param_value,
        num_kp1=len(pts1),
        num_kp2=len(pts2),
        num_raw=len(good),
        num_good=len(good),
        num_inliers=len(inliers),
        inlier_ratio=inlier_ratio,
        mean_reproj_err=reproj,
        t_detect_ms=t_det,
        t_match_ms=t_match,
    )


def plot_curves(rows: list[MatchResult]) -> None:
    FIG_DIR.mkdir(parents=True, exist_ok=True)

    def plot_one(sweep_type: str, xlabel: str, fname: str) -> None:
        fig, axes = plt.subplots(1, 2, figsize=(10, 4))
        colors = {"SIFT": "C0", "SuperPoint": "C1"}
        for method in ("SIFT", "SuperPoint"):
            sub = [r for r in rows if r.sweep_type == sweep_type and r.method == method]
            sub.sort(key=lambda r: r.param_value)
            xs = [r.param_value for r in sub]
            axes[0].plot(xs, [r.num_inliers for r in sub], "-o", label=method, color=colors[method])
            axes[1].plot(xs, [r.inlier_ratio for r in sub], "-o", label=method, color=colors[method])
        axes[0].set_xlabel(xlabel)
        axes[0].set_ylabel("RANSAC inliers")
        axes[1].set_xlabel(xlabel)
        axes[1].set_ylabel("inlier ratio")
        for ax in axes:
            ax.legend()
            ax.grid(True, alpha=0.3)
        fig.tight_layout()
        fig.savefig(FIG_DIR / fname, dpi=150)
        plt.close(fig)

    plot_one("rotation", "rotation angle (deg)", "curve_rotation.png")
    plot_one("scale", "scale factor", "curve_scale.png")


def write_csv(rows: list[MatchResult]) -> None:
    RESULT_DIR.mkdir(parents=True, exist_ok=True)
    fields = list(MatchResult.__dataclass_fields__.keys())
    with CSV_PATH.open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fields)
        w.writeheader()
        for r in rows:
            w.writerow(asdict(r))


def main() -> None:
    meta = load_meta()
    img_ref = cv2.imread(str(REF_PATH))
    if img_ref is None:
        raise FileNotFoundError(f"无法读取参考图: {REF_PATH}")

    try:
        import torch
        import kornia
    except ImportError as e:
        raise ImportError(
            "需要安装 torch 与 kornia:\n"
            "  pip install torch torchvision --index-url https://download.pytorch.org/whl/cu128\n"
            "  pip install kornia"
        ) from e

    device = "cuda" if torch.cuda.is_available() else "cpu"
    _, sp_backend = load_superpoint_class()
    print(f"python: {__import__('sys').executable}")
    print(f"torch: {torch.__version__}, cuda: {torch.cuda.is_available()}")
    print(f"kornia: {kornia.__version__}")
    print(f"SuperPoint backend: {sp_backend}, device: {device}")
    if device == "cpu" and "+cpu" in torch.__version__:
        print("提示: 当前为 CPU 版 PyTorch，SuperPoint 会较慢；可改装 cu128 版 torch。")
    if sp_backend == "lightglue":
        print("说明: 使用 LightGlue 预训练 SuperPoint（首次运行会从 GitHub 下载权重）。")

    sp = SuperPointExtractor(device=device)

    rows: list[MatchResult] = []

    for sweep_type, entries, param_key in (
        ("rotation", meta["rotation"], "angle_deg"),
        ("scale", meta["scale"], "scale"),
    ):
        for entry in entries:
            warped_path = ROOT / entry["file"]
            img_warp = cv2.imread(str(warped_path))
            if img_warp is None:
                raise RuntimeError(f"无法读取: {warped_path}")

            param_value = float(entry[param_key])
            H_gt = M_to_H(entry["M"])
            tag = f"{sweep_type}_{param_value:g}".replace(".", "p")

            print(f"\n=== {sweep_type} {param_key}={param_value} ===")
            for method in ("SIFT", "SuperPoint"):
                r = evaluate_pair(
                    method,
                    sweep_type,
                    param_value,
                    img_ref,
                    img_warp,
                    H_gt,
                    sp,
                    tag,
                )
                rows.append(r)
                print(
                    f"  [{method}] kp={r.num_kp1}/{r.num_kp2}, good={r.num_good}, "
                    f"inliers={r.num_inliers}, ratio={r.inlier_ratio:.3f}, "
                    f"reproj={r.mean_reproj_err:.2f}px, "
                    f"t={r.t_detect_ms:.0f}+{r.t_match_ms:.0f}ms"
                )

    write_csv(rows)
    plot_curves(rows)
    print(f"\n指标: {CSV_PATH.resolve()}")
    print(f"曲线与示意图: {FIG_DIR.resolve()}")


if __name__ == "__main__":
    main()
