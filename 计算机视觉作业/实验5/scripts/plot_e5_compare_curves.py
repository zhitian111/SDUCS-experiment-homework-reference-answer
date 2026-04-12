#!/usr/bin/env python3
"""读取 train_*.json 中的 hist_train / hist_iou，绘制三种变体对比曲线。"""
from __future__ import annotations

import json
import sys
from pathlib import Path

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt

_ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(_ROOT))

from src import config


def main() -> int:
    config.FIGURES_DIR.mkdir(parents=True, exist_ok=True)
    variants = [config.VARIANT_BASELINE, config.VARIANT_DILATION, config.VARIANT_SKIP]
    fig, (ax0, ax1) = plt.subplots(1, 2, figsize=(10, 3.8))
    for v in variants:
        p = config.RUNS_DIR / f"train_{v}.json"
        if not p.is_file():
            continue
        m = json.loads(p.read_text(encoding="utf-8"))
        ht = m.get("hist_train") or []
        hi = m.get("hist_iou") or []
        if ht:
            ax0.plot(range(1, len(ht) + 1), ht, label=v)
        if hi:
            ax1.plot(range(1, len(hi) + 1), hi, label=v)
    ax0.set_xlabel("epoch")
    ax0.set_ylabel("train BCE")
    ax0.legend(fontsize=8)
    ax0.grid(True, alpha=0.3)
    ax1.set_xlabel("epoch")
    ax1.set_ylabel("val IoU")
    ax1.legend(fontsize=8)
    ax1.grid(True, alpha=0.3)
    fig.tight_layout()
    out = config.FIGURES_DIR / "e5_curves_compare.png"
    fig.savefig(out, dpi=150)
    plt.close(fig)
    print(out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
