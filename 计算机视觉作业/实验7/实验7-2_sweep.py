# -*- coding: utf-8 -*-
"""实验7-2：在实验6 旋转/尺度 sweep 上评测四种特征的稳定性。

对每种特征 × 每种匹配器（nn / lightglue）统计 RANSAC 内点、内点率、重投影误差与耗时。
与实验6-2-1 使用同一套 data/sweep_meta.json 真值仿射矩阵。

用法:
  python 实验7-2_sweep.py
  python 实验7-2_sweep.py --features superpoint sift --device cuda
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

import cv2

ROOT = Path(__file__).resolve().parent
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

from e7_common import (
    EXP6,
    FEATURE_ORDER,
    MATCHER_ORDER,
    M_to_H,
    LightGluePipeline,
    MatchMetrics,
    load_meta,
    metrics_to_rows,
    plot_sweep_curves,
)

REF_PATH = ROOT.parent / "mumu.jpg"
FIG_DIR = ROOT / "figures" / "e72"
CSV_PATH = ROOT / "results" / "e72_sweep_metrics.csv"


def main() -> None:
    parser = argparse.ArgumentParser(description="实验7-2：特征 × 匹配器 sweep 评测")
    parser.add_argument(
        "--features",
        nargs="+",
        default=list(FEATURE_ORDER),
        choices=list(FEATURE_ORDER),
        help="要评测的特征子集",
    )
    parser.add_argument(
        "--matchers",
        nargs="+",
        default=list(MATCHER_ORDER),
        choices=list(MATCHER_ORDER),
    )
    parser.add_argument("--device", default=None)
    parser.add_argument("--max-keypoints", type=int, default=2048)
    args = parser.parse_args()

    import torch

    meta = load_meta()
    img_ref = cv2.imread(str(REF_PATH))
    if img_ref is None:
        raise FileNotFoundError(f"无法读取参考图: {REF_PATH}")

    device = args.device or ("cuda" if torch.cuda.is_available() else "cpu")
    print(f"python: {sys.executable}")
    print(f"torch: {torch.__version__}, cuda: {torch.cuda.is_available()}, device={device}")
    print(f"参考图: {REF_PATH.resolve()}")
    print(f"features={args.features}, matchers={args.matchers}")

    pipelines = {
        f: LightGluePipeline(f, device=device, max_num_keypoints=args.max_keypoints)
        for f in args.features
    }

    rows: list[MatchMetrics] = []

    for sweep_type, entries, param_key in (
        ("rotation", meta["rotation"], "angle_deg"),
        ("scale", meta["scale"], "scale"),
    ):
        for entry in entries:
            warped_path = EXP6 / entry["file"]
            img_warp = cv2.imread(str(warped_path))
            if img_warp is None:
                raise RuntimeError(f"无法读取: {warped_path}")

            param_value = float(entry[param_key])
            H_gt = M_to_H(entry["M"])
            tag = f"{sweep_type}_{param_value:g}".replace(".", "p")

            print(f"\n=== {sweep_type} {param_key}={param_value} ({warped_path.name}) ===")

            for feature in args.features:
                pipe = pipelines[feature]
                feats0, feats1, t_extract = pipe.extract_pair(img_ref, img_warp)
                for matcher in args.matchers:
                    m = pipe.evaluate(
                        feats0,
                        feats1,
                        matcher,
                        img_ref,
                        img_warp,
                        t_extract,
                        H_gt=H_gt,
                        sweep_type=sweep_type,
                        param_value=param_value,
                        fig_dir=FIG_DIR,
                        tag=tag,
                    )
                    rows.append(m)
                    print(
                        f"  [{feature}/{matcher}] kp={m.num_kp1}/{m.num_kp2}, "
                        f"matches={m.num_matches}, inliers={m.num_inliers}, "
                        f"ratio={m.inlier_ratio:.3f}, reproj={m.mean_reproj_err:.2f}px, "
                        f"t={m.t_extract_ms:.0f}+{m.t_match_ms:.0f}ms"
                    )

    metrics_to_rows(rows, CSV_PATH)
    plot_sweep_curves(rows, FIG_DIR)
    print(f"\n指标 CSV: {CSV_PATH.resolve()}")
    print(f"曲线与示意图: {FIG_DIR.resolve()}")


if __name__ == "__main__":
    main()
