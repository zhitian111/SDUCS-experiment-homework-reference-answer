#!/usr/bin/env python3
"""
BSDS500 常用于边缘检测基准；本实验默认选 CrackSeg9K，此脚本仅提供说明与可选校验。
数据通常从官方仓库获取：https://github.com/BIDS/BSDS500
"""
from __future__ import annotations

import argparse
import sys
from pathlib import Path


def print_manual() -> None:
    print(
        """
=== BSDS500（可选，本实验未选）===

1) 克隆或下载：https://github.com/BIDS/BSDS500

2) 建议解压到：F:/DATASET/bsds500

3) 若做边缘/边界分割，需将 human boundaries 转为二值标签（固定阈值或 ODS），
   并在报告中写明二值化规则。

本实验代码仓库以 CrackSeg9K 为主；若改用 BSDS500，需自行编写 Dataset 读取逻辑。
"""
    )


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--data_root", type=Path, default=Path("F:/DATASET/bsds500"))
    args = parser.parse_args()
    print_manual()
    args.data_root = args.data_root.resolve()
    if args.data_root.is_dir() and any(args.data_root.iterdir()):
        print(f"目录非空: {args.data_root}")
        return 0
    print(f"目录为空或不存在: {args.data_root}")
    return 1


if __name__ == "__main__":
    sys.exit(main())
