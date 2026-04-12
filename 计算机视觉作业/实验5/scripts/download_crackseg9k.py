#!/usr/bin/env python3
"""
CrackSeg9K 官方数据在 Harvard Dataverse，本脚本不自动下载大文件。
功能：1) 可选 git clone 参考仓库；2) 打印手动步骤；3) 校验本地目录结构。
"""
from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path


EXPECTED_REL = ("JPEGImages", "SegmentationClass")
OPTIONAL_REL = ("ImageSets",)


def print_manual() -> None:
    print(
        """
=== CrackSeg9K 数据获取（手动）===

1) 打开 Harvard Dataverse 数据集页面（README 要求 V4）：
   https://dataverse.harvard.edu/dataset.xhtml?persistentId=doi:10.7910/DVN/EGIEBY

2) 下载并解压全部压缩包。数据可能分为两个子文件夹，需合并到同一根目录。

3) 将合并后的根目录放到（或软链到）：
   F:/DATASET/crackseg9k

4) 期望目录结构（与官方 DeepLab 示例一致）：
   crackseg9k/
     JPEGImages/          # 原图
     SegmentationClass/   # 与图像同文件名的分割标注
     ImageSets/           # 可选；含 train.txt / val.txt，每行一个文件名

若 ImageSets 不存在，训练代码会按文件名自动配对并随机划分子集（固定 seed）。

参考代码仓库（仅论文复现代码，不含完整图像）：
   https://github.com/Dhananjay42/crackseg9k
"""
    )


def validate_root(root: Path) -> bool:
    ok = True
    for sub in EXPECTED_REL:
        p = root / sub
        if not p.is_dir():
            print(f"[缺失] 目录不存在: {p}")
            ok = False
        else:
            n = len(list(p.iterdir()))
            print(f"[OK] {p} 下条目数: {n}")
    for sub in OPTIONAL_REL:
        p = root / sub
        if p.is_dir():
            print(f"[可选] {p} 存在")
        else:
            print(f"[提示] 无 {p}，将使用自动配对 + 随机划分")
    return ok


def maybe_clone_repo(dest: Path, do_clone: bool) -> None:
    if not do_clone:
        return
    dest.mkdir(parents=True, exist_ok=True)
    target = dest / "crackseg9k-repo"
    if target.is_dir() and any(target.iterdir()):
        print(f"已存在非空目录，跳过 clone: {target}")
        return
    url = "https://github.com/Dhananjay42/crackseg9k.git"
    try:
        subprocess.run(
            ["git", "clone", "--depth", "1", url, str(target)],
            check=True,
        )
        print(f"已 clone 到: {target}")
    except (subprocess.CalledProcessError, FileNotFoundError) as e:
        print(f"git clone 失败（可忽略，仅作参考代码）: {e}")


def main() -> int:
    parser = argparse.ArgumentParser(description="CrackSeg9K 下载说明与目录校验")
    parser.add_argument(
        "--data_root",
        type=Path,
        default=Path("F:/DATASET/crackseg9k"),
        help="解压后的数据根目录",
    )
    parser.add_argument(
        "--clone_repo",
        action="store_true",
        help="尝试 shallow clone 官方 GitHub 仓库到 data_root 旁（不含数据集）",
    )
    args = parser.parse_args()

    print_manual()
    args.data_root = args.data_root.resolve()
    args.data_root.mkdir(parents=True, exist_ok=True)

    if args.clone_repo:
        maybe_clone_repo(args.data_root.parent, True)

    print(f"\n校验数据根: {args.data_root}")
    if validate_root(args.data_root):
        print("\n结构校验通过，可以运行训练。")
        return 0
    print("\n结构未就绪，请按上文完成下载与解压。")
    return 1


if __name__ == "__main__":
    sys.exit(main())
