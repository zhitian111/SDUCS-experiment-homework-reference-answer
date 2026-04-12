#!/usr/bin/env python3
"""单张图像推理 demo。"""
from __future__ import annotations

import argparse
import sys
from pathlib import Path

import numpy as np
import torch
from PIL import Image

_ROOT = Path(__file__).resolve().parent.parent
if str(_ROOT) not in sys.path:
    sys.path.insert(0, str(_ROOT))

from src import config
from src.model import TinyCrackSeg


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--image", type=Path, required=True)
    parser.add_argument("--ckpt", type=Path, required=True)
    parser.add_argument("--variant", required=True)
    parser.add_argument("--out", type=Path, default=Path("pred_mask.png"))
    parser.add_argument("--size", type=int, default=config.INPUT_SIZE)
    args = parser.parse_args()

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    pil = Image.open(args.image).convert("RGB")
    w0, h0 = pil.size
    r = pil.resize((args.size, args.size), Image.BILINEAR)
    arr = np.asarray(r, dtype=np.float32) / 255.0
    x = torch.from_numpy(arr).permute(2, 0, 1).unsqueeze(0).to(device)

    model = TinyCrackSeg(variant=args.variant).to(device)
    try:
        state = torch.load(args.ckpt, map_location=device, weights_only=False)
    except TypeError:
        state = torch.load(args.ckpt, map_location=device)
    model.load_state_dict(state["model"])
    model.eval()
    with torch.no_grad():
        logit = model(x)
        prob = torch.sigmoid(logit)[0, 0].cpu().numpy()
    mask = (prob > 0.5).astype(np.uint8) * 255
    mask_pil = Image.fromarray(mask, mode="L").resize((w0, h0), resample=Image.NEAREST)
    mask_pil.save(args.out)
    print(f"保存 {args.out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
