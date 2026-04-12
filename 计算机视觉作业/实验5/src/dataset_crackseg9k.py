"""CrackSeg9K：支持官方 Final-Dataset-Vol* 布局，以及 JPEGImages/SegmentationClass 旧布局。"""
from __future__ import annotations

import random
from pathlib import Path
from typing import List, Tuple

import numpy as np
import torch
from PIL import Image
from torch.utils.data import Dataset

from . import config


IMG_EXTS = {".jpg", ".jpeg", ".png", ".bmp"}
MASK_EXTS = {".png", ".jpg", ".jpeg", ".bmp"}


def _list_images(folder: Path) -> List[Path]:
    out: List[Path] = []
    for p in sorted(folder.iterdir()):
        if p.is_file() and p.suffix.lower() in IMG_EXTS:
            out.append(p)
    return out


def _find_mask(img_path: Path, mask_dir: Path) -> Path | None:
    stem = img_path.stem
    for ext in MASK_EXTS:
        cand = mask_dir / f"{stem}{ext}"
        if cand.is_file():
            return cand
    return None


def _read_lines(txt: Path) -> List[str]:
    lines = [ln.strip() for ln in txt.read_text(encoding="utf-8", errors="ignore").splitlines()]
    return [ln for ln in lines if ln and not ln.startswith("#")]


def _resolve_name_to_image(name: str, img_dir: Path) -> Path | None:
    p = img_dir / name
    if p.is_file():
        return p
    stem = Path(name).stem
    for ext in IMG_EXTS:
        cand = img_dir / f"{stem}{ext}"
        if cand.is_file():
            return cand
    return None


def _pairs_from_namelist(img_dir: Path, mask_dir: Path, namelist: Path) -> List[Tuple[Path, Path]]:
    pairs: List[Tuple[Path, Path]] = []
    for line in _read_lines(namelist):
        ip = _resolve_name_to_image(line, img_dir)
        if ip is None:
            continue
        mp = _find_mask(ip, mask_dir)
        if mp is not None:
            pairs.append((ip, mp))
    return pairs


def _official_vol_layout(data_root: Path) -> Tuple[Path, List[Path], Path, Path] | None:
    """
    返回 (mask_dir, image_dirs, train_txt, test_txt)；若不存在则 None。
    图像可能在 Vol1/Images 与 Vol2/Images-2；掩膜统一在 Vol1/Final_Masks/Masks。
    """
    vol1 = data_root / "Final-Dataset-Vol1"
    vol2 = data_root / "Final-Dataset-Vol2"
    mask_dir = vol1 / "Final_Masks" / "Masks"
    train_txt = vol1 / "Final_Masks" / "train.txt"
    test_txt = vol1 / "Final_Masks" / "test.txt"
    if not mask_dir.is_dir() or not train_txt.is_file() or not test_txt.is_file():
        return None
    image_dirs: List[Path] = []
    im1 = vol1 / "Images"
    im2 = vol2 / "Images-2"
    if im1.is_dir():
        image_dirs.append(im1)
    if im2.is_dir():
        image_dirs.append(im2)
    if not image_dirs:
        return None
    return mask_dir, image_dirs, train_txt, test_txt


def _pairs_from_official_lists(
    mask_dir: Path,
    image_dirs: List[Path],
    namelist: Path,
) -> List[Tuple[Path, Path]]:
    pairs: List[Tuple[Path, Path]] = []
    for line in _read_lines(namelist):
        name = Path(line).name
        mp = mask_dir / name
        if not mp.is_file():
            continue
        ip: Path | None = None
        for idir in image_dirs:
            cand = idir / name
            if cand.is_file():
                ip = cand
                break
        if ip is not None:
            pairs.append((ip, mp))
    return pairs


def collect_train_val_pairs(data_root: Path, seed: int) -> Tuple[List[Tuple[Path, Path]], List[Tuple[Path, Path]]]:
    data_root = Path(data_root)
    img_dir = data_root / "JPEGImages"
    mask_dir_legacy = data_root / "SegmentationClass"

    off = _official_vol_layout(data_root)
    if off is not None:
        mdir, idirs, train_txt, test_txt = off
        tr = _pairs_from_official_lists(mdir, idirs, train_txt)
        va = _pairs_from_official_lists(mdir, idirs, test_txt)
        if tr and va:
            return tr, va

    if img_dir.is_dir() and mask_dir_legacy.is_dir():
        train_txt = data_root / "ImageSets" / "train.txt"
        val_txt = data_root / "ImageSets" / "val.txt"
        if train_txt.is_file() and val_txt.is_file():
            tr = _pairs_from_namelist(img_dir, mask_dir_legacy, train_txt)
            va = _pairs_from_namelist(img_dir, mask_dir_legacy, val_txt)
            if tr or va:
                return tr, va

        all_pairs: List[Tuple[Path, Path]] = []
        for ip in _list_images(img_dir):
            mp = _find_mask(ip, mask_dir_legacy)
            if mp is not None:
                all_pairs.append((ip, mp))
        if not all_pairs:
            raise RuntimeError(f"未找到任何图像–掩膜配对，检查目录: {data_root}")
        rng = random.Random(seed)
        idx = list(range(len(all_pairs)))
        rng.shuffle(idx)
        n_val = max(1, len(idx) // 5)
        va_idx = set(idx[:n_val])
        tr_idx = [i for i in idx if i not in va_idx]
        tr = [all_pairs[i] for i in tr_idx]
        va = [all_pairs[i] for i in va_idx]
        return tr, va

    raise FileNotFoundError(
        f"无法解析数据布局：既无 Final-Dataset-Vol1/Final_Masks，也无 JPEGImages/SegmentationClass：{data_root}"
    )


def subset_pairs(
    pairs: List[Tuple[Path, Path]], n: int, seed: int, salt: int
) -> Tuple[List[Tuple[Path, Path]], List[int]]:
    rng = random.Random(seed + salt * 7919)
    order = list(range(len(pairs)))
    rng.shuffle(order)
    take = min(n, len(order))
    sel = order[:take]
    sub = [pairs[i] for i in sel]
    return sub, sel


def _pil_rgb_to_chw01(img: Image.Image) -> torch.Tensor:
    arr = np.asarray(img, dtype=np.float32) / 255.0
    return torch.from_numpy(arr).permute(2, 0, 1)


class CrackSegDataset(Dataset):
    def __init__(
        self,
        pairs: List[Tuple[Path, Path]],
        input_size: int,
        augment: bool,
    ) -> None:
        self.pairs = pairs
        self.input_size = input_size
        self.augment = augment

    def __len__(self) -> int:
        return len(self.pairs)

    def __getitem__(self, i: int) -> dict:
        ip, mp = self.pairs[i]
        img = Image.open(ip).convert("RGB")
        mask = Image.open(mp).convert("L")
        sz = (self.input_size, self.input_size)

        if self.augment and random.random() < 0.5:
            img = img.transpose(Image.FLIP_LEFT_RIGHT)
            mask = mask.transpose(Image.FLIP_LEFT_RIGHT)

        img = img.resize(sz, Image.BILINEAR)
        mask = mask.resize(sz, Image.NEAREST)

        x = _pil_rgb_to_chw01(img)
        m = np.array(mask, dtype=np.float32)
        if m.max() > 1.0:
            m = (m > 127).astype(np.float32)
        else:
            m = (m > 0.5).astype(np.float32)
        y = torch.from_numpy(m).unsqueeze(0)
        return {"image": x, "mask": y, "path": str(ip)}


def load_datasets(
    data_root: Path | None = None,
    seed: int | None = None,
    train_n: int | None = None,
    val_n: int | None = None,
    input_size: int | None = None,
) -> Tuple[CrackSegDataset, CrackSegDataset]:
    data_root = Path(data_root or config.DATA_ROOT)
    seed = int(seed if seed is not None else config.RANDOM_SEED)
    train_n = int(train_n if train_n is not None else config.TRAIN_SUBSET)
    val_n = int(val_n if val_n is not None else config.VAL_SUBSET)
    input_size = int(input_size if input_size is not None else config.INPUT_SIZE)

    tr_all, va_all = collect_train_val_pairs(data_root, seed)
    tr_sub, _ = subset_pairs(tr_all, train_n, seed, 1)
    va_sub, _ = subset_pairs(va_all, val_n, seed, 2)
    train_ds = CrackSegDataset(tr_sub, input_size, augment=True)
    val_ds = CrackSegDataset(va_sub, input_size, augment=False)
    return train_ds, val_ds
