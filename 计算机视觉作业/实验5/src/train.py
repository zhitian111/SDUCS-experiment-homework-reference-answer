#!/usr/bin/env python3
"""训练轻量 CNN，支持 baseline / dilation / skip；支持断点续训与小 batch。"""
from __future__ import annotations

import argparse
import json
import re
import sys
import time
from pathlib import Path
from typing import Any

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
import torch
import torch.nn as nn
from torch.utils.data import DataLoader
from tqdm import tqdm

_ROOT = Path(__file__).resolve().parent.parent
if str(_ROOT) not in sys.path:
    sys.path.insert(0, str(_ROOT))

from src import config
from src.dataset_crackseg9k import load_datasets
from src.metrics import accumulate_batch, aggregate
from src.model import TinyCrackSeg, count_parameters


def _infer_completed_epochs(log_path: Path) -> int:
    if not log_path.is_file():
        return 0
    mx = 0
    for line in log_path.read_text(encoding="utf-8", errors="replace").splitlines():
        m = re.match(r"epoch (\d+):", line.strip())
        if m:
            mx = max(mx, int(m.group(1)))
    return mx


def _cuda_gc(device: torch.device) -> None:
    if device.type == "cuda":
        torch.cuda.empty_cache()


@torch.no_grad()
def evaluate(model: nn.Module, loader: DataLoader, device: torch.device) -> dict:
    model.eval()
    tot = {"tp": torch.zeros(1, device=device), "fp": torch.zeros(1, device=device), "fn": torch.zeros(1, device=device)}
    for batch in loader:
        x = batch["image"].to(device)
        y = batch["mask"].to(device)
        logits = model(x)
        s = accumulate_batch(logits, y)
        tot["tp"] += s["tp"]
        tot["fp"] += s["fp"]
        tot["fn"] += s["fn"]
    return aggregate(tot)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--variant", default=config.VARIANT_BASELINE, choices=[
        config.VARIANT_BASELINE, config.VARIANT_DILATION, config.VARIANT_SKIP,
    ])
    parser.add_argument("--data_root", type=Path, default=config.DATA_ROOT)
    parser.add_argument("--epochs", type=int, default=config.EPOCHS, help="训练结束 epoch 编号（总目标），例如 30")
    parser.add_argument("--batch_size", type=int, default=config.BATCH_SIZE)
    parser.add_argument("--lr", type=float, default=config.LEARNING_RATE)
    parser.add_argument("--seed", type=int, default=config.RANDOM_SEED)
    parser.add_argument("--pos_weight", type=float, default=config.POS_WEIGHT)
    parser.add_argument(
        "--resume",
        type=Path,
        default=None,
        help="断点 .pt：完整断点含优化器；也可为 best_<variant>.pt（仅权重，需配合 --start_epoch 或日志推断）",
    )
    parser.add_argument(
        "--from_last",
        action="store_true",
        help="从 checkpoints/last_<variant>.pt 续训（须已存在，由上一轮正常跑完至少 1 个 epoch 写出）",
    )
    parser.add_argument(
        "--start_epoch",
        type=int,
        default=None,
        help="仅权重恢复时：已完成的 epoch 数（下一轮从 start_epoch+1 开始）。不设则尝试读 e5_train_<variant>.log",
    )
    args = parser.parse_args()

    torch.manual_seed(args.seed)
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

    train_ds, val_ds = load_datasets(data_root=args.data_root, seed=args.seed)
    pin = device.type == "cuda"
    train_loader = DataLoader(
        train_ds, batch_size=args.batch_size, shuffle=True, num_workers=config.NUM_WORKERS, pin_memory=pin
    )
    val_loader = DataLoader(val_ds, batch_size=args.batch_size, shuffle=False, num_workers=config.NUM_WORKERS)

    model = TinyCrackSeg(variant=args.variant).to(device)
    n_params = count_parameters(model)
    pos_w = torch.tensor([args.pos_weight], device=device)
    criterion = nn.BCEWithLogitsLoss(pos_weight=pos_w)
    opt = torch.optim.Adam(model.parameters(), lr=args.lr)

    config.FIGURES_DIR.mkdir(parents=True, exist_ok=True)
    config.RUNS_DIR.mkdir(parents=True, exist_ok=True)
    config.CKPT_DIR.mkdir(parents=True, exist_ok=True)

    best_path = config.CKPT_DIR / f"best_{args.variant}.pt"
    last_path = config.CKPT_DIR / f"last_{args.variant}.pt"
    log_path = config.RUNS_DIR / f"e5_train_{args.variant}.log"

    epoch_done = 0
    hist_train: list[float] = []
    hist_iou: list[float] = []
    epoch_seconds: list[float] = []
    best_iou = -1.0
    log_lines: list[str] = []

    resume_path = Path(args.resume) if args.resume is not None else None
    if args.from_last:
        if not last_path.is_file():
            print(f"错误: 指定了 --from_last 但不存在 {last_path}")
            return 1
        resume_path = last_path

    if resume_path is not None and resume_path.is_file():
        try:
            payload = torch.load(resume_path, map_location=device, weights_only=False)
        except TypeError:
            payload = torch.load(resume_path, map_location=device)
        model.load_state_dict(payload["model"])
        if payload.get("optimizer") is not None:
            opt.load_state_dict(payload["optimizer"])
            epoch_done = int(payload.get("epoch_done", 0))
            hist_train = list(payload.get("hist_train") or [])
            hist_iou = list(payload.get("hist_iou") or [])
            epoch_seconds = list(payload.get("epoch_seconds") or [])
            best_iou = float(payload.get("best_val_iou", -1.0))
            prev_log = payload.get("log_lines")
            if isinstance(prev_log, list):
                log_lines = [str(x) for x in prev_log]
            print(f"已从完整断点恢复: {resume_path} epoch_done={epoch_done} best_iou={best_iou}")
        else:
            se = args.start_epoch
            if se is None:
                se = _infer_completed_epochs(log_path)
            epoch_done = int(se)
            print(
                f"已加载权重（无优化器状态）: {resume_path}，从 epoch {epoch_done + 1} 续到 {args.epochs}；"
                f"若 epoch 估计不准请使用 --start_epoch"
            )
    else:
        if args.resume is not None:
            print(f"警告: 未找到断点 {args.resume}，从头训练")

    def log_msg(s: str) -> None:
        print(s)
        log_lines.append(s)

    if epoch_done >= args.epochs:
        log_msg(f"已完成目标 epoch（{epoch_done} >= {args.epochs}），无需继续训练")
        return 0

    log_msg(
        f"variant={args.variant} device={device} batch_size={args.batch_size} "
        f"train_n={len(train_ds)} val_n={len(val_ds)} params={n_params} "
        f"resume_from_epoch_done={epoch_done} target_epoch={args.epochs}"
    )

    for epoch in range(epoch_done + 1, args.epochs + 1):
        t0 = time.perf_counter()
        model.train()
        running = 0.0
        n = 0
        for batch in tqdm(train_loader, desc=f"epoch {epoch}/{args.epochs}"):
            x = batch["image"].to(device)
            y = batch["mask"].to(device)
            opt.zero_grad(set_to_none=True)
            logits = model(x)
            loss = criterion(logits, y)
            loss.backward()
            opt.step()
            running += loss.item() * x.size(0)
            n += x.size(0)
        train_loss = running / max(n, 1)
        val_m = evaluate(model, val_loader, device)
        _cuda_gc(device)
        dt = time.perf_counter() - t0
        hist_train.append(train_loss)
        hist_iou.append(val_m["iou"])
        epoch_seconds.append(dt)
        line = f"epoch {epoch}: train_loss={train_loss:.4f} val_iou={val_m['iou']:.4f} val_f1={val_m['f1']:.4f} time={dt:.1f}s"
        log_msg(line)

        if val_m["iou"] > best_iou:
            best_iou = val_m["iou"]
            torch.save({"model": model.state_dict(), "variant": args.variant, "iou": best_iou}, best_path)

        torch.save(
            {
                "model": model.state_dict(),
                "optimizer": opt.state_dict(),
                "epoch_done": epoch,
                "hist_train": hist_train,
                "hist_iou": hist_iou,
                "epoch_seconds": epoch_seconds,
                "best_val_iou": best_iou,
                "variant": args.variant,
                "batch_size": args.batch_size,
                "lr": args.lr,
                "log_lines": log_lines,
            },
            last_path,
        )

    fig, ax = plt.subplots(figsize=(6, 4))
    ax.plot(hist_train, label="train BCE")
    ax.plot(hist_iou, label="val IoU")
    ax.set_xlabel("epoch")
    ax.legend()
    fig.tight_layout()
    loss_fig = config.FIGURES_DIR / f"e5_loss_{args.variant}.png"
    fig.savefig(loss_fig, dpi=150)
    plt.close(fig)

    mean_ep = sum(epoch_seconds) / len(epoch_seconds) if epoch_seconds else 0.0
    meta = {
        "variant": args.variant,
        "params": n_params,
        "best_val_iou": best_iou,
        "epochs": args.epochs,
        "epoch_done": len(hist_train),
        "mean_epoch_sec": mean_ep,
        "train_size": len(train_ds),
        "val_size": len(val_ds),
        "checkpoint": str(best_path),
        "last_checkpoint": str(last_path),
        "batch_size": args.batch_size,
        "hist_train": hist_train,
        "hist_iou": hist_iou,
    }
    (config.RUNS_DIR / f"train_{args.variant}.json").write_text(json.dumps(meta, indent=2), encoding="utf-8")
    log_path.write_text("\n".join(log_lines) + "\n", encoding="utf-8")
    log_msg(f"已保存: {loss_fig}, {best_path}, {last_path}, best_val_iou={best_iou}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
