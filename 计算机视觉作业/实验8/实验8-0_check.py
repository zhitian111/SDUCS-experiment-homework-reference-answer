# -*- coding: utf-8 -*-
"""实验8 前置检查：数据文件与 OpenCV 检测器是否可用。

用法（在 venv 中）:
  python 实验8-0_check.py
"""

from __future__ import annotations

import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
if str(ROOT) not in sys.path:
  sys.path.insert(0, str(ROOT))

from e8_common import REFERENCE_RESULT_PATH, TEMPLATE_PATH, VIDEO_PATH, create_detector


def main() -> None:
  ok = True
  print("=== 实验8 环境检查 ===\n")

  for label, path in [
    ("平面模板", TEMPLATE_PATH),
    ("跟踪视频", VIDEO_PATH),
    ("参考结果图", REFERENCE_RESULT_PATH),
  ]:
    if path.exists():
      print(f"[OK] {label}: {path.resolve()}")
    else:
      print(f"[缺失] {label}: {path.resolve()}")
      ok = False

  try:
    import cv2
    import numpy as np

    print(f"\n[OK] opencv={cv2.__version__}, numpy={np.__version__}")

    for name in ("orb", "akaze"):
      detector, norm = create_detector(name)
      print(f"     - {name.upper()} 检测器可用, norm={norm}")
      del detector
  except Exception as e:
    print(f"\n[缺失] OpenCV 检测器初始化失败: {e}")
    ok = False

  if ok:
    print("\n可以运行:")
    print("  python 实验8-1_planar_tracking.py")
    print("  python 实验8-1_planar_tracking.py --detector akaze")
    print("  python 实验8-1_planar_tracking.py --output output/tracking_result.mp4")
  else:
    print("\n请先补齐缺失项，并在 venv 中安装:")
    print("  pip install -r requirements-e8.txt")
    sys.exit(1)


if __name__ == "__main__":
  main()
