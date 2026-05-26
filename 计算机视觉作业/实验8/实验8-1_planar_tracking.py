# -*- coding: utf-8 -*-
"""实验8.1：实时平面跟踪。

基于平面模板图像，在视频中检测并跟踪平面物体，用蓝色线框标出物体边沿。
默认使用 ORB 特征以保证实时性，也可切换为 AKAZE。

用法（在 venv 中）:
  python 实验8-0_check.py
  python 实验8-1_planar_tracking.py
  python 实验8-1_planar_tracking.py --detector akaze --output output/tracking_result.mp4
"""

from __future__ import annotations

import argparse
import sys
import time
from pathlib import Path

import cv2

ROOT = Path(__file__).resolve().parent
if str(ROOT) not in sys.path:
  sys.path.insert(0, str(ROOT))

from e8_common import (
  OUTPUT_DIR,
  TEMPLATE_PATH,
  VIDEO_PATH,
  DetectorName,
  PlanarTracker,
)


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="实验8.1 实时平面跟踪")
  parser.add_argument("--template", type=Path, default=TEMPLATE_PATH, help="平面模板图像")
  parser.add_argument("--video", type=Path, default=VIDEO_PATH, help="待跟踪视频")
  parser.add_argument(
    "--detector",
    choices=("orb", "akaze"),
    default="akaze",
    help="特征检测器；AKAZE 更稳，ORB 更快",
  )
  parser.add_argument(
    "--ratio",
    type=float,
    default=0.7,
    help="Lowe ratio 阈值，越小越严格（默认 0.7）",
  )
  parser.add_argument(
    "--output",
    type=Path,
    default=None,
    help="输出视频路径，例如 output/tracking_result.mp4",
  )
  parser.add_argument(
    "--max-width",
    type=int,
    default=960,
    help="匹配阶段的最大帧宽，缩小可提速",
  )
  parser.add_argument("--smooth", type=float, default=0.55, help="角点平滑系数，越小越不易乱飞")
  parser.add_argument("--no-display", action="store_true", help="不弹出预览窗口")
  return parser.parse_args()


def open_video(path: Path) -> cv2.VideoCapture:
  cap = cv2.VideoCapture(str(path))
  if not cap.isOpened():
    raise RuntimeError(f"无法打开视频: {path.resolve()}")
  return cap


def create_writer(path: Path, fps: float, size: tuple[int, int]) -> cv2.VideoWriter:
  path.parent.mkdir(parents=True, exist_ok=True)
  fourcc = cv2.VideoWriter_fourcc(*"mp4v")
  writer = cv2.VideoWriter(str(path), fourcc, fps, size)
  if not writer.isOpened():
    raise RuntimeError(f"无法创建输出视频: {path.resolve()}")
  return writer


def run_tracking(
  template_path: Path,
  video_path: Path,
  detector: DetectorName,
  output_path: Path | None,
  max_width: int,
  smooth: float,
  ratio: float,
  show_window: bool,
) -> None:
  template = cv2.imread(str(template_path))
  if template is None:
    raise FileNotFoundError(f"模板读取失败: {template_path.resolve()}")

  tracker = PlanarTracker(
    template,
    detector_name=detector,
    ratio=ratio,
    smooth_alpha=smooth,
    process_max_width=max_width,
  )

  cap = open_video(video_path)
  fps = cap.get(cv2.CAP_PROP_FPS) or 25.0
  width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
  height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
  frame_count = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))

  writer = create_writer(output_path, fps, (width, height)) if output_path else None
  window_name = "实验8.1 平面跟踪 (q 退出)"

  print(f"模板: {template_path.resolve()}")
  print(f"视频: {video_path.resolve()} ({width}x{height}, {fps:.2f} fps, {frame_count} 帧)")
  print(f"检测器: {detector.upper()}, 模板特征点: {len(tracker.template_kp)}")
  if output_path:
    print(f"输出: {output_path.resolve()}")

  tracked_frames = 0
  idx = 0
  t_start = time.perf_counter()

  while True:
    ok, frame = cap.read()
    if not ok:
      break

    corners, stats = tracker.track(frame)
    vis = PlanarTracker.draw_wireframe(frame, corners)
    tracked_frames += int(stats.tracked)

    elapsed = time.perf_counter() - t_start
    inst_fps = (idx + 1) / elapsed if elapsed > 0 else 0.0
    status = "TRACK" if stats.tracked else "LOST "
    reason = f" ({stats.reject_reason})" if stats.reject_reason else ""
    overlay = (
      f"{status} | fps={inst_fps:.1f} | good={stats.good_matches} "
      f"| inliers={stats.inliers} ({stats.inlier_ratio:.0%}) "
      f"| err={stats.reproj_err:.1f}{reason}"
    )
    cv2.putText(
      vis,
      overlay,
      (12, 28),
      cv2.FONT_HERSHEY_SIMPLEX,
      0.65,
      (0, 255, 0) if stats.tracked else (0, 0, 255),
      2,
      cv2.LINE_AA,
    )

    if writer is not None:
      writer.write(vis)
    if show_window:
      cv2.imshow(window_name, vis)
      if cv2.waitKey(1) & 0xFF == ord("q"):
        break

    idx += 1

  cap.release()
  if writer is not None:
    writer.release()
  if show_window:
    cv2.destroyAllWindows()

  total = max(idx, 1)
  avg_fps = idx / max(time.perf_counter() - t_start, 1e-6)
  print(
    f"\n完成: 处理 {idx} 帧, 跟踪成功 {tracked_frames} 帧 "
    f"({100.0 * tracked_frames / total:.1f}%), 平均 {avg_fps:.1f} fps"
  )


def main() -> None:
  args = parse_args()
  output = args.output
  if output is None and args.no_display:
    output = OUTPUT_DIR / "tracking_result.mp4"

  run_tracking(
    template_path=args.template,
    video_path=args.video,
    detector=args.detector,
    output_path=output,
    max_width=args.max_width,
    smooth=args.smooth,
    ratio=args.ratio,
    show_window=not args.no_display,
  )


if __name__ == "__main__":
  main()
