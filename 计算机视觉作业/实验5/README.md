# 实验 E5：卷积神经网络——裂缝语义分割（CrackSeg9K 子集）

本实验在 **CrackSeg9K** 上做**二分类语义分割**（裂缝=1，背景=0），自研轻量 **Encoder–Decoder**，并对比：

- `baseline`：对称编解码 + bottleneck 卷积  
- `dilation`：bottleneck 使用 **空洞卷积** 扩大感受野  
- `skip`：在解码阶段与 **第三层 encoder 特征做一次拼接融合**（非完整 U-Net）

**未选 BSDS500 边缘任务的原因**：裂缝数据集掩膜与图像一一对应，标签处理简单；子集 500 train / 100 val 与课程实验算力匹配。

## 环境

优先使用课程共用虚拟环境：

```powershell
f:\Homework\自然语言处理作业\.venv\Scripts\Activate.ps1
cd f:\Homework\计算机视觉作业\实验5
pip install -r requirements.txt
```

若需 GPU 版 PyTorch，请按 [pytorch.org](https://pytorch.org/) 选择对应命令安装。

说明：数据加载与推理仅依赖 `Pillow`，无需安装 `torchvision`（减小依赖体积）。

## 数据

数据必须放在 **`F:\DATASET\crackseg9k`**，目录结构（与官方 DeepLab 示例一致）：

```
crackseg9k/
  JPEGImages/
  SegmentationClass/
  ImageSets/          # 可选
    train.txt
    val.txt
```

获取方式与校验：

```powershell
python scripts/download_crackseg9k.py --data_root F:/DATASET/crackseg9k
```

完整图像需从 **Harvard Dataverse** 下载（见脚本打印说明）。

**冒烟测试（无真实数据时）**：生成合成小数据集并训练 2 个 epoch，仅验证代码可跑通。

```powershell
python scripts/make_toy_crack_data.py --out F:/DATASET/crackseg9k_toy
python -m src.train --variant baseline --data_root F:/DATASET/crackseg9k_toy --epochs 2 --batch_size 4
```

## 训练与评估

在 `实验5` 目录下执行（模块方式）：

```powershell
python -m src.train --variant baseline
python -m src.train --variant dilation
python -m src.train --variant skip
```

### 显存不足（OOM）与断点续训

- 默认 `config.BATCH_SIZE` 已改为 **4**；仍 OOM 可加 `--batch_size 2` 或 `1`。
- 每个 epoch 结束会写入 `checkpoints/last_<variant>.pt`（含模型、优化器、曲线与日志文本）。若存在该文件，下次可直接：

```powershell
python -m src.train --variant baseline --batch_size 2 --from_last
```

（`--from_last` 会读取 `checkpoints/last_baseline.pt`。）

- 若崩溃后**只有** `best_<variant>.pt`（没有 `last_*.pt`），说明上一轮可能死在某个 epoch 中途；可用权重暖启动，并用 `--start_epoch` 指定**已跑完的最大 epoch 编号**（与控制台/日志里 `epoch N:` 的 N 一致），例如已从 1 训到 14 后崩溃：

```powershell
python -m src.train --variant baseline --batch_size 2 --resume checkpoints/best_baseline.pt --start_epoch 14 --epochs 30
```

下一轮将从 epoch 15 训到 30；优化器会重新初始化。若 `runs/e5_train_<variant>.log` 仍在，也可省略 `--start_epoch`，脚本会尝试从日志推断已完成的 epoch。

评估与其它脚本：

```powershell
python -m src.eval --ckpt checkpoints/best_baseline.pt --variant baseline
python -m src.eval --ckpt checkpoints/best_dilation.pt --variant dilation
python -m src.eval --ckpt checkpoints/best_skip.pt --variant skip

python scripts/summarize_runs.py
```

产出：

- `checkpoints/best_*.pt`：验证集 IoU 最优权重  
- `figures/e5_loss_*.png`：训练损失与验证 IoU 曲线  
- `figures/e5_metrics_*.txt`、`runs/train_*.json`  
- `figures/e5_sample_*_*.png`：原图 | GT | 预测叠加  

单张推理：

```powershell
python -m src.infer --image path\to\img.jpg --ckpt checkpoints/best_dilation.pt --variant dilation --out pred.png
```

## 报告

使用 XeLaTeX 编译 `CV202300130183宋浩宇E5.tex`（插图来自 `figures/`）。
