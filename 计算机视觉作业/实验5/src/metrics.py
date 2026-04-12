"""二值分割指标（逐 batch 累加）。"""
from __future__ import annotations

import torch


@torch.no_grad()
def accumulate_batch(logits: torch.Tensor, target: torch.Tensor, thr: float = 0.5) -> dict:
    prob = torch.sigmoid(logits)
    pred = (prob > thr).float()
    t = target.float()
    tp = (pred * t).sum()
    fp = (pred * (1.0 - t)).sum()
    fn = ((1.0 - pred) * t).sum()
    return {"tp": tp, "fp": fp, "fn": fn}


def aggregate(stats: dict) -> dict:
    tp, fp, fn = stats["tp"], stats["fp"], stats["fn"]
    prec = (tp / (tp + fp + 1e-8)).item()
    rec = (tp / (tp + fn + 1e-8)).item()
    f1 = (2 * prec * rec / (prec + rec + 1e-8))
    union = tp + fp + fn
    iou = (tp / (union + 1e-8)).item()
    return {"iou": iou, "f1": f1, "precision": prec, "recall": rec}
