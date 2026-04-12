#!/usr/bin/env python3
"""加载 best 权重，在验证子集上算指标并导出可视化。"""
from __future__ import annotations

import argparse
import sys
from pathlib import Path

import numpy as np
import torch
import torch.nn as nn
from PIL import Image
from torch.utils.data import DataLoader

_ROOT = Path(__file__).resolve().parent.parent
if str(_ROOT) not in sys.path:
    sys.path.insert(0, str(_ROOT))

from src import config
from src.dataset_crackseg9k import load_datasets
from src.metrics import accumulate_batch, aggregate
from src.model import TinyCrackSeg


def _save_triplet(rgb01: np.ndarray, gt_u8: np.ndarray, pred_u8: np.ndarray, path: Path) -> None:
    """横向拼接：原图 | GT | 叠加。"""
    h, w, _ = rgb01.shape
    base = (np.clip(rgb01 * 255.0, 0, 255)).astype(np.uint8)
    g3 = np.stack([gt_u8, gt_u8, gt_u8], axis=-1)
    overlay = base.copy()
    red = np.zeros_like(overlay)
    red[:, :, 0] = pred_u8
    overlay = (overlay.astype(np.float32) * 0.75 + red.astype(np.float32) * 0.25).astype(np.uint8)
    row = np.concatenate([base, g3, overlay], axis=1)
    Image.fromarray(row).save(path)


@torch.no_grad()
def run_eval(
    ckpt: Path,
    variant: str,
    data_root: Path,
    seed: int,
    device: torch.device,
    num_vis: int,
) -> dict:
    _, val_ds = load_datasets(data_root=data_root, seed=seed)
    loader = DataLoader(val_ds, batch_size=4, shuffle=False, num_workers=config.NUM_WORKERS)

    model = TinyCrackSeg(variant=variant).to(device)
    try:
        state = torch.load(ckpt, map_location=device, weights_only=False)
    except TypeError:
        state = torch.load(ckpt, map_location=device)
    model.load_state_dict(state["model"])
    model.eval()

    tot = {"tp": torch.zeros(1, device=device), "fp": torch.zeros(1, device=device), "fn": torch.zeros(1, device=device)}
    vis_done = 0
    config.FIGURES_DIR.mkdir(parents=True, exist_ok=True)

    for batch in loader:
        x = batch["image"].to(device)
        y = batch["mask"].to(device)
        logits = model(x)
        s = accumulate_batch(logits, y)
        tot["tp"] += s["tp"]
        tot["fp"] += s["fp"]
        tot["fn"] += s["fn"]

        if vis_done < num_vis:
            prob = torch.sigmoid(logits)
            pred = (prob > 0.5).float()
            bsz = x.size(0)
            for j in range(bsz):
                if vis_done >= num_vis:
                    break
                img = x[j].cpu().numpy().transpose(1, 2, 0)
                gt = (y[j, 0].cpu().numpy() * 255.0).astype(np.uint8)
                pr = (pred[j, 0].cpu().numpy() * 255.0).astype(np.uint8)
                _save_triplet(img, gt, pr, config.FIGURES_DIR / f"e5_sample_{variant}_{vis_done}.png")
                vis_done += 1

    return aggregate(tot)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--ckpt", type=Path, required=True)
    parser.add_argument("--variant", required=True, choices=[
        config.VARIANT_BASELINE, config.VARIANT_DILATION, config.VARIANT_SKIP,
    ])
    parser.add_argument("--data_root", type=Path, default=config.DATA_ROOT)
    parser.add_argument("--seed", type=int, default=config.RANDOM_SEED)
    parser.add_argument("--num_vis", type=int, default=6)
    args = parser.parse_args()

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    m = run_eval(args.ckpt, args.variant, args.data_root, args.seed, device, args.num_vis)

    lines = [
        f"variant={args.variant}",
        f"iou={m['iou']:.6f}",
        f"f1={m['f1']:.6f}",
        f"precision={m['precision']:.6f}",
        f"recall={m['recall']:.6f}",
    ]
    out_txt = config.FIGURES_DIR / f"e5_metrics_{args.variant}.txt"
    out_txt.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print("\n".join(lines))
    print(f"写入 {out_txt}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
