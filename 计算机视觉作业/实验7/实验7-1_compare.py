# -*- coding: utf-8 -*-
"""实验7-1：在「原图 vs 随机变换图」上对比 NN 与 LightGlue。

四种特征：SuperPoint, DISK, ALIKED, SIFT（均为 LightGlue 提供的提取器）。
匹配方式：
  - nn：互最近邻（与实验6 SuperPoint 的 mutual NN 一致，作为基线）
  - lightglue：LightGlue 学习型匹配器

需先运行实验6-0 生成 images/mumu_random.jpg（可选，也可用 --img2 指定第二张图）。

用法:
  python 实验7-1_compare.py
  python 实验7-1_compare.py --device cuda --max-keypoints 2048
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
    FEATURE_ORDER,
    MATCHER_ORDER,
    RANDOM_IMG,
    REF_PATH,
    LightGluePipeline,
    MatchMetrics,
    metrics_to_rows,
)

FIG_DIR = ROOT / "figures" / "e71"
CSV_PATH = ROOT / "results" / "e71_pair_metrics.csv"


def main() -> None:
    parser = argparse.ArgumentParser(description="实验7-1：NN vs LightGlue（单对图像）")
    parser.add_argument("--img1", type=Path, default=REF_PATH, help="参考图")
    parser.add_argument("--img2", type=Path, default=RANDOM_IMG, help="待匹配图")
    parser.add_argument("--device", default=None, help="cuda / cpu，默认自动")
    parser.add_argument("--max-keypoints", type=int, default=2048)
    args = parser.parse_args()

    if not args.img1.exists():
        raise FileNotFoundError(f"找不到图1: {args.img1.resolve()}")
    if not args.img2.exists():
        raise FileNotFoundError(
            f"找不到图2: {args.img2.resolve()}\n"
            "请先运行实验6: python 实验6-0.py，或用 --img2 指定路径"
        )

    import torch

    device = args.device or ("cuda" if torch.cuda.is_available() else "cpu")
    print(f"device={device}, max_keypoints={args.max_keypoints}")
    print(f"图1: {args.img1.resolve()}")
    print(f"图2: {args.img2.resolve()}")

    img1 = cv2.imread(str(args.img1))
    img2 = cv2.imread(str(args.img2))
    if img1 is None or img2 is None:
        raise RuntimeError("图像读取失败")

    rows: list[MatchMetrics] = []
    pipelines: dict[str, LightGluePipeline] = {}

    for feature in FEATURE_ORDER:
        print(f"\n=== {feature} ===")
        pipe = LightGluePipeline(feature, device=device, max_num_keypoints=args.max_keypoints)
        pipelines[feature] = pipe
        feats0, feats1, t_extract = pipe.extract_pair(img1, img2)
        for matcher in MATCHER_ORDER:
            m = pipe.evaluate(
                feats0,
                feats1,
                matcher,
                img1,
                img2,
                t_extract,
                sweep_type="pair",
                param_value=0.0,
                fig_dir=FIG_DIR,
                tag="pair",
            )
            rows.append(m)
            print(
                f"  [{matcher}] kp={m.num_kp1}/{m.num_kp2}, matches={m.num_matches}, "
                f"inliers={m.num_inliers}, ratio={m.inlier_ratio:.3f}, "
                f"t={m.t_extract_ms:.0f}+{m.t_match_ms:.0f}ms"
            )

    metrics_to_rows(rows, CSV_PATH)
    print(f"\n指标 CSV: {CSV_PATH.resolve()}")
    print(f"匹配示意图: {FIG_DIR.resolve()}")


if __name__ == "__main__":
    main()
