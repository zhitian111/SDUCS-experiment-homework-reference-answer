# -*- coding: utf-8 -*-
"""实验6.2：生成旋转/尺度可控序列，并记录真值仿射矩阵 M。

原图固定为 ../mumu.jpg。运行后得到 data/sweep_rotation、data/sweep_scale 与 sweep_meta.json。
"""

from __future__ import annotations

import json
from pathlib import Path

import cv2
import numpy as np

ROOT = Path(__file__).resolve().parent
SRC = ROOT / ".." / "mumu.jpg"
DATA_DIR = ROOT / "data"
ROT_DIR = DATA_DIR / "sweep_rotation"
SCALE_DIR = DATA_DIR / "sweep_scale"
META_PATH = DATA_DIR / "sweep_meta.json"

ROTATION_ANGLES = [0, 15, 30, 45, 60]
SCALE_FACTORS = [0.6, 0.75, 0.9, 1.0, 1.15, 1.3]
BORDER = (255, 255, 255)


def warp_affine(img: np.ndarray, angle: float, scale: float) -> tuple[np.ndarray, list[list[float]]]:
    h, w = img.shape[:2]
    center = (w / 2.0, h / 2.0)
    M = cv2.getRotationMatrix2D(center, angle, scale)
    out = cv2.warpAffine(
        img,
        M,
        (w, h),
        flags=cv2.INTER_LINEAR,
        borderMode=cv2.BORDER_CONSTANT,
        borderValue=BORDER,
    )
    return out, M.tolist()


def main() -> None:
    if not SRC.exists():
        raise FileNotFoundError(f"找不到原图: {SRC.resolve()}")

    img = cv2.imread(str(SRC))
    if img is None:
        raise RuntimeError(f"无法读取: {SRC}")

    ROT_DIR.mkdir(parents=True, exist_ok=True)
    SCALE_DIR.mkdir(parents=True, exist_ok=True)

    rotation_entries = []
    for angle in ROTATION_ANGLES:
        warped, M = warp_affine(img, angle=angle, scale=1.0)
        name = f"mumu_rot_{angle:03d}.jpg"
        out_path = ROT_DIR / name
        cv2.imwrite(str(out_path), warped)
        rotation_entries.append(
            {
                "file": str(out_path.relative_to(ROOT)),
                "angle_deg": angle,
                "scale": 1.0,
                "M": M,
            }
        )
        print(f"rotation {angle:3d}° -> {out_path.name}")

    scale_entries = []
    for scale in SCALE_FACTORS:
        warped, M = warp_affine(img, angle=0.0, scale=scale)
        pct = int(round(scale * 100))
        name = f"mumu_scale_{pct:03d}.jpg"
        out_path = SCALE_DIR / name
        cv2.imwrite(str(out_path), warped)
        scale_entries.append(
            {
                "file": str(out_path.relative_to(ROOT)),
                "angle_deg": 0.0,
                "scale": scale,
                "M": M,
            }
        )
        print(f"scale {scale:.2f} -> {out_path.name}")

    meta = {
        "reference": str(SRC.resolve()),
        "rotation": rotation_entries,
        "scale": scale_entries,
    }
    META_PATH.parent.mkdir(parents=True, exist_ok=True)
    META_PATH.write_text(json.dumps(meta, ensure_ascii=False, indent=2), encoding="utf-8")
    print(f"\n元数据已保存: {META_PATH.resolve()}")


if __name__ == "__main__":
    main()

