#!/usr/bin/env python3
"""汇总 train_*.json 与 e5_metrics_*.txt，生成 figures/e5_compare.txt 供报告引用。"""
from __future__ import annotations

import json
import sys
from pathlib import Path

_ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(_ROOT))

from src import config


def parse_metrics_txt(p: Path) -> dict:
    d: dict[str, float] = {}
    for line in p.read_text(encoding="utf-8").splitlines():
        if "=" in line:
            k, v = line.split("=", 1)
            try:
                d[k.strip()] = float(v.strip())
            except ValueError:
                pass
    return d


def main() -> int:
    fig_dir = config.FIGURES_DIR
    run_dir = config.RUNS_DIR
    fig_dir.mkdir(parents=True, exist_ok=True)

    rows = []
    for variant in [config.VARIANT_BASELINE, config.VARIANT_DILATION, config.VARIANT_SKIP]:
        jf = run_dir / f"train_{variant}.json"
        mf = fig_dir / f"e5_metrics_{variant}.txt"
        params = None
        ep_t = None
        if jf.is_file():
            meta = json.loads(jf.read_text(encoding="utf-8"))
            params = meta.get("params")
            ep_t = meta.get("mean_epoch_sec")
        m = parse_metrics_txt(mf) if mf.is_file() else {}
        rows.append(
            {
                "variant": variant,
                "params": params,
                "iou": m.get("iou"),
                "f1": m.get("f1"),
                "epoch_sec": ep_t,
            }
        )

    lines = ["# variant | params | IoU | F1 | mean_epoch_sec"]
    for r in rows:
        lines.append(
            f"{r['variant']}\t{r['params']}\t{r['iou']}\t{r['f1']}\t{r['epoch_sec']}"
        )
    out = fig_dir / "e5_compare.txt"
    out.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"写入 {out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
