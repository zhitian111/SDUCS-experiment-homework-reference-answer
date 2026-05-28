# -*- coding: utf-8 -*-
"""
自然语言处理课程实验：统一运行时配置。

用法（放在各实验 .py 最顶部，须早于 import transformers / huggingface_hub）:

    import sys
    from pathlib import Path
    _root = Path(__file__).resolve().parent.parent
    if str(_root) not in sys.path:
        sys.path.insert(0, str(_root))
    import nlp_runtime
    nlp_runtime.setup()

本机参数：脚本「本机配置」区已填写的项优先；留空字符串或 None 时再从环境变量读取。
查看生效项: python nlp_runtime.py
"""
from __future__ import annotations

import os
import random
import time
from pathlib import Path

# ========== 本机配置（改这里即可）==========
# 已填写的项优先；留空 "" 或 None 时再从环境变量读取
PROXY = "http://127.0.0.1:7897"
DISABLE_PROXY = None

HF_HOME = r"F:\Downloads\huggingface"
TMP_DIR = ""
PIP_CACHE_DIR = ""

USE_MIRROR = None
HF_DOWNLOAD_TIMEOUT = ""
DOWNLOAD_RETRIES = None

RANDOM_SEED = None

HF_TOKEN = ""
# ==========================================

NLP_ROOT = Path(__file__).resolve().parent
_setup_done: Path | None = None


def _env_str(*keys: str) -> str:
    for k in keys:
        v = os.environ.get(k, "").strip()
        if v:
            return v
    return ""


def _cfg_str(script_val: str, *env_keys: str, default: str = "") -> str:
    if script_val:
        return script_val
    env = _env_str(*env_keys)
    if env:
        return env
    return default


def _cfg_bool(script_val: bool | None, *env_keys: str, default: bool = False) -> bool:
    if script_val is not None:
        return script_val
    for k in env_keys:
        v = os.environ.get(k, "").strip().lower()
        if v in ("1", "true", "yes", "on"):
            return True
        if v in ("0", "false", "no", "off"):
            return False
    return default


def _cfg_int(script_val: int | None, *env_keys: str, default: int = 0) -> int:
    if script_val is not None:
        return script_val
    env = _env_str(*env_keys)
    if env:
        return int(env)
    return default


def set_random_seed(seed: int | None = None) -> int:
    s = seed if seed is not None else _cfg_int(RANDOM_SEED, "NLP_RANDOM_SEED", default=42)
    random.seed(s)
    os.environ["PYTHONHASHSEED"] = str(s)
    return s


def seed_numpy_torch(seed: int | None = None) -> int:
    s = set_random_seed(seed)
    try:
        import numpy as np

        np.random.seed(s)
    except ImportError:
        pass
    try:
        import torch

        torch.manual_seed(s)
        if torch.cuda.is_available():
            torch.cuda.manual_seed_all(s)
    except ImportError:
        pass
    return s


def setup(
    *,
    seed: int | None = None,
    hf_home: str | Path | None = None,
    proxy: str | None = None,
    use_mirror: bool | None = None,
) -> Path:
    global _setup_done
    if _setup_done is not None:
        return _setup_done

    set_random_seed(seed)

    proxy_url = proxy or _cfg_str(PROXY, "NLP_PROXY", "NLP_WEEK10_PROXY", "HTTP_PROXY")
    disable_proxy = _cfg_bool(
        DISABLE_PROXY, "NLP_DISABLE_PROXY", "NLP_WEEK10_DISABLE_PROXY", default=False
    )
    if not disable_proxy and proxy_url:
        for k in ("HTTP_PROXY", "HTTPS_PROXY", "http_proxy", "https_proxy"):
            os.environ.setdefault(k, proxy_url)
        os.environ.setdefault("NO_PROXY", "localhost,127.0.0.1,::1")
        os.environ.setdefault("no_proxy", "localhost,127.0.0.1,::1")

    hf_default = str(NLP_ROOT / "_hf_cache")
    hf_path = Path(hf_home or _cfg_str(HF_HOME, "NLP_HF_HOME", "HF_HOME", default=hf_default))
    hf_path.mkdir(parents=True, exist_ok=True)
    hub_cache = hf_path / "hub"
    hub_cache.mkdir(parents=True, exist_ok=True)
    os.environ["HF_HOME"] = str(hf_path)
    os.environ["HF_HUB_CACHE"] = str(hub_cache)
    os.environ["TRANSFORMERS_CACHE"] = str(hub_cache)
    os.environ["HUGGINGFACE_HUB_CACHE"] = str(hub_cache)

    tmp_default = str(hf_path / "_tmp")
    tmp_root = Path(_cfg_str(TMP_DIR, "NLP_TMP", "NLP_WEEK10_TMP", default=tmp_default))
    tmp_root.mkdir(parents=True, exist_ok=True)
    for k in ("TMP", "TEMP", "TMPDIR"):
        os.environ[k] = str(tmp_root)

    pip_cache = _cfg_str(PIP_CACHE_DIR, "NLP_PIP_CACHE_DIR", "PIP_CACHE_DIR")
    if pip_cache:
        os.environ["PIP_CACHE_DIR"] = pip_cache

    mirror_on = use_mirror if use_mirror is not None else _cfg_bool(
        USE_MIRROR, "NLP_USE_MIRROR", "NLP_WEEK10_USE_MIRROR", default=False
    )
    if mirror_on:
        os.environ.setdefault("HF_ENDPOINT", "https://hf-mirror.com")

    if "HF_HUB_DISABLE_XET" not in os.environ:
        os.environ["HF_HUB_DISABLE_XET"] = "1"
    os.environ.setdefault(
        "HF_HUB_DOWNLOAD_TIMEOUT",
        _cfg_str(HF_DOWNLOAD_TIMEOUT, "NLP_HF_DOWNLOAD_TIMEOUT", default="1200"),
    )
    os.environ.setdefault("HF_HUB_DISABLE_SYMLINKS_WARNING", "1")

    token = _cfg_str(HF_TOKEN, "HF_TOKEN", "HUGGING_FACE_HUB_TOKEN")
    if token and not os.environ.get("HF_TOKEN"):
        os.environ["HF_TOKEN"] = token

    _setup_done = hf_path
    return hf_path


def hf_home() -> Path:
    return setup()


def hub_token() -> str | None:
    t = HF_TOKEN.strip() if HF_TOKEN else ""
    if not t:
        t = _env_str("HF_TOKEN", "HUGGING_FACE_HUB_TOKEN")
    return t or None


def clean_incomplete_downloads(root: Path | None = None) -> int:
    hub = (root or hf_home()) / "hub"
    if not hub.is_dir():
        return 0
    n = 0
    for p in hub.rglob("*.incomplete"):
        try:
            p.unlink(missing_ok=True)
            n += 1
        except OSError:
            pass
    return n


def download_model(model_id: str, *, retries: int | None = None) -> str:
    from huggingface_hub import snapshot_download

    root = setup()
    retries = retries if retries is not None else _cfg_int(
        DOWNLOAD_RETRIES, "NLP_DOWNLOAD_RETRIES", default=3
    )
    cleaned = clean_incomplete_downloads(root)
    if cleaned:
        print(f"已清理 {cleaned} 个未完成下载片段")

    token = hub_token()
    cur = os.environ.get("HF_ENDPOINT", "https://huggingface.co").rstrip("/")
    plans: list[tuple[str, bool]] = [
        ("https://hf-mirror.com", False),
        ("https://huggingface.co", True),
    ]
    if cur == "https://hf-mirror.com":
        plans = [("https://hf-mirror.com", False), ("https://huggingface.co", True)]

    proxy_keys = ("HTTP_PROXY", "HTTPS_PROXY", "http_proxy", "https_proxy")
    proxy_url = _cfg_str(PROXY, "NLP_PROXY", "NLP_WEEK10_PROXY", default="http://127.0.0.1:7897")
    last_err: Exception | None = None
    for attempt in range(1, retries + 1):
        for endpoint, use_proxy in plans:
            saved = {k: os.environ.get(k) for k in proxy_keys}
            os.environ["HF_ENDPOINT"] = endpoint
            if use_proxy:
                for k in proxy_keys:
                    os.environ[k] = proxy_url
            else:
                for k in proxy_keys:
                    os.environ.pop(k, None)
            try:
                kw: dict = {"repo_id": model_id, "max_workers": 1}
                if token:
                    kw["token"] = token
                print(f"第{attempt}轮  Endpoint={endpoint}  代理={'开' if use_proxy else '关'}")
                return snapshot_download(**kw)
            except Exception as exc:
                last_err = exc
                print(f"下载失败: {type(exc).__name__}: {exc}")
            finally:
                for k, v in saved.items():
                    if v is None:
                        os.environ.pop(k, None)
                    else:
                        os.environ[k] = v
        clean_incomplete_downloads(root)
        if attempt < retries:
            time.sleep(3)
    if last_err is not None:
        raise last_err
    raise RuntimeError("模型下载失败")


def print_runtime_info() -> None:
    setup()
    print(f"随机种子: {os.environ.get('PYTHONHASHSEED', '（未设置）')}")
    print(f"代理: {os.environ.get('HTTPS_PROXY', '（未设置）')}")
    print(f"HF_HOME: {os.environ.get('HF_HOME', '（未设置）')}")
    print(f"HF_HUB_CACHE: {os.environ.get('HF_HUB_CACHE', '（未设置）')}")
    print(f"TMP: {os.environ.get('TEMP', '（未设置）')}")
    if os.environ.get("PIP_CACHE_DIR"):
        print(f"PIP_CACHE_DIR: {os.environ['PIP_CACHE_DIR']}")
    print(f"HF_ENDPOINT: {os.environ.get('HF_ENDPOINT', 'https://huggingface.co')}")
    legacy = Path.home() / ".cache" / "huggingface"
    if legacy.exists():
        print(f"提示: C 盘旧缓存仍存在: {legacy}，当前实验下载不使用该目录，确认 F 盘模型可用后可删除")


if __name__ == "__main__":
    setup()
    print_runtime_info()
