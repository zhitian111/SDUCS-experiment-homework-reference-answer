# -*- coding: utf-8 -*-
"""实验7 前置检查：原图、实验6 sweep 数据、LightGlue 后端是否可用。

用法（在 venv 中）:
  python 实验7-0_check.py
"""

from __future__ import annotations

import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

from e7_common import EXP6, META_PATH, RANDOM_IMG, REF_PATH, check_backend


def main() -> None:
    ok = True
    print("=== 实验7 环境检查 ===\n")

    if REF_PATH.exists():
        print(f"[OK] 参考图: {REF_PATH.resolve()}")
    else:
        print(f"[缺失] 参考图: {REF_PATH.resolve()}")
        ok = False

    if META_PATH.exists():
        print(f"[OK] sweep 元数据: {META_PATH.resolve()}")
    else:
        print(f"[缺失] {META_PATH.resolve()}")
        print("       请在实验6运行: python 实验6-2-0_sweep.py")
        ok = False

    rot_dir = EXP6 / "data" / "sweep_rotation"
    scale_dir = EXP6 / "data" / "sweep_scale"
    if rot_dir.is_dir() and any(rot_dir.glob("*.jpg")):
        print(f"[OK] 旋转序列: {rot_dir}")
    else:
        print(f"[缺失] 旋转序列目录或图像: {rot_dir}")
        ok = False

    if scale_dir.is_dir() and any(scale_dir.glob("*.jpg")):
        print(f"[OK] 尺度序列: {scale_dir}")
    else:
        print(f"[缺失] 尺度序列目录或图像: {scale_dir}")
        ok = False

    if RANDOM_IMG.exists():
        print(f"[OK] 随机变换图（实验7-1 用）: {RANDOM_IMG.resolve()}")
    else:
        print(f"[可选] 随机变换图不存在，实验7-1 需先运行实验6: python 实验6-0.py")
        print(f"       路径: {RANDOM_IMG.resolve()}")

    try:
        backend = check_backend()
        import torch

        device = "cuda" if torch.cuda.is_available() else "cpu"
        print(f"\n[OK] 后端: {backend}")
        print(f"     torch={torch.__version__}, device={device}")

        if backend == "kornia":
            import kornia

            print(f"     kornia={kornia.__version__}")
            print("     说明: 使用 kornia 内置 LightGlue，无需 pip install git+LightGlue")
            print("     首次运行会通过 torch.hub 下载权重（若 GitHub 不通，见 README 镜像说明）")
        else:
            print("     说明: 使用官方 lightglue 包")

        from e7_common import FEATURE_ORDER, LightGluePipeline

        for feat in FEATURE_ORDER:
            LightGluePipeline(feat, device=device, max_num_keypoints=64)
            print(f"      - {feat} OK")
    except Exception as e:
        err = str(e)
        print(f"\n[缺失] {err}")
        if "SSL" in err or "urlopen" in err or "github" in err.lower():
            print("权重下载失败。请运行: powershell -File 下载匹配权重.ps1")
        ok = False

    if ok:
        print("\n可以运行:")
        print("  python 实验7-1_compare.py")
        print("  python 实验7-2_sweep.py")
    else:
        print("\n请先补齐上述缺失项。")
        print("推荐解释器: ..\\.venv-cv\\Scripts\\python.exe")
        print("创建环境: powershell -File 创建视觉实验环境.ps1")
        sys.exit(1)


if __name__ == "__main__":
    main()
