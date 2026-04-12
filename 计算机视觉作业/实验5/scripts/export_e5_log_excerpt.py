#!/usr/bin/env python3
"""合并各变体训练日志首尾片段，供报告引用（纯 ASCII 行，避免 verbatim 编码问题）。"""
from __future__ import annotations

import json
import sys
from pathlib import Path

_ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(_ROOT))

from src import config


def main() -> int:
    lines: list[str] = []
    for v in [config.VARIANT_BASELINE, config.VARIANT_DILATION, config.VARIANT_SKIP]:
        logf = config.RUNS_DIR / f"e5_train_{v}.log"
        jsf = config.RUNS_DIR / f"train_{v}.json"
        lines.append(f"=== {v} ===")
        if logf.is_file():
            raw = logf.read_text(encoding="utf-8", errors="replace").splitlines()
            head = raw[:3]
            tail = raw[-5:] if len(raw) > 8 else raw[3:]
            lines.extend(head)
            lines.append("...")
            lines.extend(tail)
        if jsf.is_file():
            m = json.loads(jsf.read_text(encoding="utf-8"))
            lines.append(
                f"json: best_val_iou={m.get('best_val_iou')} params={m.get('params')} mean_epoch_sec={m.get('mean_epoch_sec')}"
            )
        lines.append("")
    out = config.RUNS_DIR / "e5_log_excerpt.txt"
    out.write_text("\n".join(lines), encoding="utf-8")
    # 复制到 figures 供与 tex 同目录引用时可选
    alt = config.FIGURES_DIR / "e5_log_excerpt.txt"
    alt.write_text("\n".join(lines), encoding="utf-8")
    print(out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
