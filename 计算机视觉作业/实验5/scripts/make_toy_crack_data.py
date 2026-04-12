#!/usr/bin/env python3
"""生成极小合成裂缝数据，仅用于代码冒烟（非真实实验结果）。"""
from __future__ import annotations

import argparse
import sys
from pathlib import Path

import numpy as np
from PIL import Image


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--out", type=Path, default=Path("F:/DATASET/crackseg9k_toy"))
    parser.add_argument("--n_train", type=int, default=40)
    parser.add_argument("--n_val", type=int, default=12)
    args = parser.parse_args()

    root = args.out
    jdir = root / "JPEGImages"
    mdir = root / "SegmentationClass"
    iset = root / "ImageSets"
    for d in (jdir, mdir, iset):
        d.mkdir(parents=True, exist_ok=True)

    def write_pair(i: int, split: str) -> str:
        name = f"{split}_{i:04d}.png"
        img = np.random.randint(40, 200, (320, 480, 3), dtype=np.uint8)
        mask = np.zeros((320, 480), dtype=np.uint8)
        mask[100:220, 200:280] = 255
        Image.fromarray(img).save(jdir / name)
        Image.fromarray(mask, mode="L").save(mdir / name)
        return name

    tr = [write_pair(i, "tr") for i in range(args.n_train)]
    va = [write_pair(i, "va") for i in range(args.n_val)]
    (iset / "train.txt").write_text("\n".join(tr) + "\n", encoding="utf-8")
    (iset / "val.txt").write_text("\n".join(va) + "\n", encoding="utf-8")
    print(f"已写入 {root}，可用 --data_root 指向该路径做冒烟训练。")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
