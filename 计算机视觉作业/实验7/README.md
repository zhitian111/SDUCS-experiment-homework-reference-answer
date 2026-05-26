# 实验7：LightGlue 图像匹配

对比 **互最近邻（NN）** 与 **LightGlue** 匹配器，在 **SuperPoint / DISK / ALIKED / SIFT** 四种特征下测试旋转、尺度变换的匹配稳定性。

## 环境准备（重要：勿用损坏的 BloodCulture venv）

若 `import torch` 报 `c10.dll` / `WinError 1114`，说明当前 Python 环境里 **PyTorch 已损坏**（与实验7 代码无关）。请改用 Homework 下独立 venv：

```powershell
cd F:\Homework\计算机视觉作业\实验7
powershell -ExecutionPolicy Bypass -File 创建视觉实验环境.ps1
```

解释器路径：`F:\Homework\计算机视觉作业\.venv-cv\Scripts\python.exe`（在 PyCharm/Cursor 里选这个）

或手动：

```bash
cd 计算机视觉作业
py -3.12 -m venv .venv-cv
.venv-cv\Scripts\pip install "numpy>=1.26,<2" torch torchvision --index-url https://download.pytorch.org/whl/cpu
.venv-cv\Scripts\pip install -r 实验7/requirements-e7.txt -i https://pypi.tuna.tsinghua.edu.cn/simple
```

**不要**再 `pip install git+https://github.com/cvg/LightGlue.git`（国内常 SSL 失败）。实验7 使用 **kornia>=0.8** 内置 LightGlue。

实验7 代码**默认使用 kornia 内置的 LightGlue**（与官方算法一致），实验6 环境升级 kornia 即可。

### 若仍想安装官方 lightglue 包

GitHub 不通时使用镜像脚本：

```powershell
powershell -ExecutionPolicy Bypass -File 安装LightGlue-镜像.ps1
```

或手动：从 [ghproxy 镜像](https://ghproxy.net/https://github.com/cvg/LightGlue/archive/refs/heads/main.zip) 下载 ZIP，解压到 `vendor/LightGlue`，再 `pip install -e vendor/LightGlue`。

### 权重下载失败时

kornia 会通过 `torch.hub` 从 `github.com/cvg/LightGlue/releases` 拉取 `*_lightglue.pth`。若仍超时，可设置 HuggingFace 镜像后再运行：

```powershell
$env:HF_ENDPOINT = "https://hf-mirror.com"
```

或将权重手动放到 torch hub 缓存目录（运行一次报错后，根据终端提示的路径放置）。

## 实验6 数据

```bash
cd ../实验6
python 实验6-2-0_sweep.py
python 实验6-0.py          # 可选，供实验7-1
```

## 运行

```bash
python 实验7-0_check.py
python 实验7-1_compare.py
python 实验7-2_sweep.py
```

有 GPU：`python 实验7-2_sweep.py --device cuda`

## 输出

| 脚本 | 结果 |
|------|------|
| 实验7-1 | `results/e71_pair_metrics.csv`，`figures/e71/` |
| 实验7-2 | `results/e72_sweep_metrics.csv`，`figures/e72/` |

## 与实验6 的对应

- **NN**：与实验6-2-1 的 `mutual_nn_match` 相同（互最近邻 + RANSAC）
- **LightGlue**：学习型匹配
- **SIFT**：kornia `SIFTFeature`（RootSIFT），与 LightGlue 的 sift 权重配套
