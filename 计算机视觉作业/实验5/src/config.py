"""实验路径与超参（Windows 使用正斜杠 Path 可跨平台）。"""
from pathlib import Path

# 数据根：官方为 Final-Dataset-Vol1/Vol2；亦兼容 JPEGImages / SegmentationClass
DATA_ROOT = Path("F:/DATASET/crackseg9k")

# 工程根（含 figures、checkpoints）
PROJECT_ROOT = Path(__file__).resolve().parent.parent
FIGURES_DIR = PROJECT_ROOT / "figures"
RUNS_DIR = PROJECT_ROOT / "runs"
CKPT_DIR = PROJECT_ROOT / "checkpoints"

# 子集（与计划一致，可按算力改小）
RANDOM_SEED = 42
TRAIN_SUBSET = 500
VAL_SUBSET = 100

# 训练
INPUT_SIZE = 256
# 显存紧张时可改 2；训练可用 --batch_size 覆盖
BATCH_SIZE = 4
NUM_WORKERS = 0  # Windows 下设 0 更稳
LEARNING_RATE = 1e-3
EPOCHS = 30
POS_WEIGHT = 8.0  # 裂缝像素少，BCE 正类权重

# 模型变体名
VARIANT_BASELINE = "baseline"
VARIANT_DILATION = "dilation"
VARIANT_SKIP = "skip"
