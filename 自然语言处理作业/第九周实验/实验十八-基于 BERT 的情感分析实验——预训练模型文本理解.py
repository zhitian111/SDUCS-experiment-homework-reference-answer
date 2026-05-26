# -*- coding: utf-8 -*-
from __future__ import annotations

import os
from pathlib import Path

if "HF_HUB_DISABLE_XET" not in os.environ:
    os.environ["HF_HUB_DISABLE_XET"] = "1"
os.environ.setdefault("HF_HUB_DOWNLOAD_TIMEOUT", "600")

BASE_DIR = Path(__file__).resolve().parent
DATA_PATH = BASE_DIR / "exp-9.2-data.txt"

SA_MODEL = os.environ.get(
    "NLP_WEEK9_SA_MODEL",
    "uer/roberta-base-finetuned-jd-binary-chinese",
)

EXTRA_SENTENCES = [
    "这个电影不算差。",
    "服务态度不算好。",
    "今天天气是阴天。",
]


def read_sentences(path: Path) -> list[str]:
    if not path.is_file():
        return []
    return [ln.strip() for ln in path.read_text(encoding="utf-8").splitlines() if ln.strip()]


def label_zh(raw: str) -> str:
    u = (raw or "").upper()
    if u in ("LABEL_1", "POSITIVE", "POS", "5 STARS", "4 STARS", "4-5 STARS"):
        return "偏正面"
    if u in ("LABEL_0", "NEGATIVE", "NEG", "1 STAR", "2 STARS", "1-2 STARS"):
        return "偏负面"
    if "NEU" in u or "中性" in raw:
        return "中性"
    if "POS" in u:
        return "偏正面"
    if "NEG" in u:
        return "偏负面"
    return raw or "未知"


def build_pipeline():
    import torch
    from transformers import pipeline

    device = 0 if torch.cuda.is_available() else -1
    token = os.environ.get("HF_TOKEN") or os.environ.get("HUGGING_FACE_HUB_TOKEN")
    kw = {
        "task": "sentiment-analysis",
        "model": SA_MODEL,
        "tokenizer": SA_MODEL,
        "device": device,
        "trust_remote_code": True,
    }
    if token and token.strip():
        kw["token"] = token.strip()
    return pipeline(**kw)


def predict_one(clf, text: str) -> tuple[str, float, str]:
    r = clf(text[:512])[0]
    lab = str(r.get("label", ""))
    score = float(r.get("score", 0.0))
    return lab, score, label_zh(lab)


def run_block(clf, title: str, sentences: list[str]) -> None:
    if not sentences:
        return
    print(f"\n--- {title} ---")
    for i, s in enumerate(sentences, 1):
        lab, score, zh = predict_one(clf, s)
        print(f"[{i}] {s}")
        print(f"    label={lab}  score={score:.6f}  解读={zh}")


def main() -> None:
    print(f"数据文件: {DATA_PATH}")
    print(f"模型: {SA_MODEL}")

    try:
        clf = build_pipeline()
    except Exception as e:
        print(f"模型加载失败: {type(e).__name__}: {e}")
        raise SystemExit(1) from e

    sentences = read_sentences(DATA_PATH)
    run_block(clf, "任务书示例句", sentences)
    run_block(clf, "复杂与否定句式补充", EXTRA_SENTENCES)


if __name__ == "__main__":
    main()
