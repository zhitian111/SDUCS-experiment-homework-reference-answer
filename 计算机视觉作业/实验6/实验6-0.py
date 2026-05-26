# -*- coding: utf-8 -*-
"""从 ../mumu.jpg 随机生成变换图，供特征匹配实验使用。"""

import argparse
import json
import random
from pathlib import Path

import cv2
import numpy as np

ROOT = Path(__file__).resolve().parent
SRC = ROOT / ".." / "mumu.jpg"
OUT_DIR = ROOT / "images"
OUT_PATH = OUT_DIR / "mumu_random.jpg"
PARAMS_PATH = OUT_DIR / "mumu_random_params.json"


def random_transform(img: np.ndarray, rng: random.Random) -> tuple[np.ndarray, dict]:
    h, w = img.shape[:2]
    center = (w / 2.0, h / 2.0)

    angle = rng.uniform(-35.0, 35.0)
    scale = rng.uniform(0.75, 1.05)
    tx = rng.uniform(-0.08 * w, 0.08 * w)
    ty = rng.uniform(-0.08 * h, 0.08 * h)

    M = cv2.getRotationMatrix2D(center, angle, scale)
    M[0, 2] += tx
    M[1, 2] += ty

    border = (255, 255, 255)
    if img.ndim == 2:
        border = 255
    warped = cv2.warpAffine(
        img,
        M,
        (w, h),
        flags=cv2.INTER_LINEAR,
        borderMode=cv2.BORDER_CONSTANT,
        borderValue=border,
    )

    alpha = rng.uniform(0.85, 1.15)
    beta = rng.uniform(-25.0, 25.0)
    warped = cv2.convertScaleAbs(warped, alpha=alpha, beta=beta)

    blur_k = None
    if rng.random() < 0.35:
        blur_k = int(rng.choice([3, 5]))
        warped = cv2.GaussianBlur(
            warped, (blur_k, blur_k), sigmaX=rng.uniform(0.3, 1.0)
        )

    params = {
        "angle_deg": round(angle, 2),
        "scale": round(scale, 3),
        "tx_px": round(tx, 1),
        "ty_px": round(ty, 1),
        "brightness_alpha": round(alpha, 3),
        "brightness_beta": round(beta, 1),
        "gaussian_blur": blur_k,
    }
    return warped, params


def main() -> None:
    parser = argparse.ArgumentParser(description="随机变换 ../mumu.jpg 并保存到 images/")
    parser.add_argument(
        "--seed",
        type=int,
        default=None,
        help="随机种子；指定后每次生成相同变换，便于复现实验",
    )
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        default=OUT_PATH,
        help=f"输出路径，默认 {OUT_PATH.name}",
    )
    args = parser.parse_args()

    if not SRC.exists():
        raise FileNotFoundError(f"找不到原图: {SRC.resolve()}")

    img = cv2.imread(str(SRC))
    if img is None:
        raise RuntimeError(f"无法读取图像: {SRC.resolve()}")

    rng = random.Random(args.seed)
    out_img, params = random_transform(img, rng)

    args.output.parent.mkdir(parents=True, exist_ok=True)
    if not cv2.imwrite(str(args.output), out_img):
        raise RuntimeError(f"保存失败: {args.output}")

    meta = {
        "source": str(SRC.resolve()),
        "output": str(args.output.resolve()),
        "seed": args.seed,
        **params,
    }
    PARAMS_PATH.parent.mkdir(parents=True, exist_ok=True)
    PARAMS_PATH.write_text(json.dumps(meta, ensure_ascii=False, indent=2), encoding="utf-8")

    print(f"原图: {SRC.resolve()}")
    print(f"已保存: {args.output.resolve()}")
    print(f"参数记录: {PARAMS_PATH.resolve()}")
    print("变换参数:", json.dumps(params, ensure_ascii=False))


if __name__ == "__main__":
    main()
