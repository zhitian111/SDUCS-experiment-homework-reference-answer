"""
轻量 Encoder–Decoder 分割头（自研小网，非完整 U-Net 论文结构）。
- baseline：对称上下采样 + bottleneck 卷积
- dilation：bottleneck 使用空洞卷积扩大感受野
- skip：仅一层 encoder 特征与 decoder 拼接后再卷积融合
"""
from __future__ import annotations

import torch
import torch.nn as nn
import torch.nn.functional as F

from . import config


class ConvBNReLU(nn.Module):
    def __init__(
        self,
        in_ch: int,
        out_ch: int,
        k: int = 3,
        stride: int = 1,
        padding: int | None = None,
        dilation: int = 1,
    ) -> None:
        super().__init__()
        if padding is None:
            padding = dilation * (k // 2)
        self.conv = nn.Conv2d(in_ch, out_ch, k, stride=stride, padding=padding, dilation=dilation, bias=False)
        self.bn = nn.BatchNorm2d(out_ch)
        self.act = nn.ReLU(inplace=True)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.act(self.bn(self.conv(x)))


class Down(nn.Module):
    def __init__(self, in_ch: int, out_ch: int) -> None:
        super().__init__()
        self.block = ConvBNReLU(in_ch, out_ch)
        self.pool = nn.MaxPool2d(2)

    def forward(self, x: torch.Tensor) -> tuple[torch.Tensor, torch.Tensor]:
        y = self.block(x)
        return self.pool(y), y


class Up(nn.Module):
    def __init__(self, in_ch: int, out_ch: int) -> None:
        super().__init__()
        self.conv = ConvBNReLU(in_ch, out_ch)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        x = F.interpolate(x, scale_factor=2, mode="bilinear", align_corners=False)
        return self.conv(x)


class TinyCrackSeg(nn.Module):
    def __init__(self, variant: str = config.VARIANT_BASELINE) -> None:
        super().__init__()
        self.variant = variant
        c1, c2, c3, c4 = 32, 64, 96, 128

        self.in_conv = ConvBNReLU(3, c1)
        self.d1 = Down(c1, c2)
        self.d2 = Down(c2, c3)
        self.d3 = Down(c3, c4)
        self.d4 = Down(c4, c4)

        dil = 2 if variant == config.VARIANT_DILATION else 1
        self.bot1 = ConvBNReLU(c4, c4, dilation=dil)
        self.bot2 = ConvBNReLU(c4, c4, dilation=dil)

        self.u1 = Up(c4, c4)
        self.u2 = Up(c4, c3)
        self.merge_skip = None
        if variant == config.VARIANT_SKIP:
            # d3 的 skip 为 Down(c3,c4) 中 block 输出，通道数为 c4；u2 输出为 c3
            self.merge_skip = ConvBNReLU(c3 + c4, c3)
        self.u3 = Up(c3, c2)
        self.u4 = Up(c2, c1)
        self.out_conv = nn.Conv2d(c1, 1, kernel_size=1)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        x = self.in_conv(x)
        x, _ = self.d1(x)
        x, _ = self.d2(x)
        x, s2 = self.d3(x)
        x, _ = self.d4(x)
        x = self.bot1(x)
        x = self.bot2(x)
        x = self.u1(x)
        x = self.u2(x)
        if self.merge_skip is not None:
            if s2.shape[2:] != x.shape[2:]:
                s2 = F.interpolate(s2, size=x.shape[2:], mode="bilinear", align_corners=False)
            x = self.merge_skip(torch.cat([x, s2], dim=1))
        x = self.u3(x)
        x = self.u4(x)
        return self.out_conv(x)


def count_parameters(m: nn.Module) -> int:
    return sum(p.numel() for p in m.parameters() if p.requires_grad)
