from __future__ import annotations

import os
from pathlib import Path

if "HF_HUB_DISABLE_XET" not in os.environ:
    os.environ["HF_HUB_DISABLE_XET"] = "1"
os.environ.setdefault("HF_HUB_DOWNLOAD_TIMEOUT", "600")

BASE_DIR = Path(__file__).resolve().parent
DATA_PATH = BASE_DIR / "exp-8.2-data.txt"

MODEL_NAME = os.environ.get("NLP_WEEK8_MT_MODEL", "Helsinki-NLP/opus-mt-zh-en")

DEFAULT_SENTENCES = [
    "我喜欢自然语言处理。",
    "今天天气很好。",
    "人工智能正在快速发展。",
    "机器翻译非常有趣。",
    "深度学习改变了很多领域。",
]


def read_sentences(path: Path) -> list[str]:
    if not path.is_file():
        return list(DEFAULT_SENTENCES)
    out: list[str] = []
    for raw in path.read_text(encoding="utf-8").splitlines():
        s = raw.strip()
        if s:
            out.append(s)
    return out if out else list(DEFAULT_SENTENCES)


def load_model():
    import torch
    from transformers import AutoModelForSeq2SeqLM, AutoTokenizer

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
    model = AutoModelForSeq2SeqLM.from_pretrained(MODEL_NAME)
    model.to(device)
    model.eval()
    return tokenizer, model, device


def translate_batch(
    tokenizer,
    model,
    device,
    sentences: list[str],
    max_new_tokens: int = 128,
    num_beams: int = 4,
) -> list[str]:
    import torch

    enc = tokenizer(
        sentences,
        return_tensors="pt",
        padding=True,
        truncation=True,
        max_length=256,
    )
    enc = {k: v.to(device) for k, v in enc.items()}
    with torch.no_grad():
        out_ids = model.generate(
            **enc,
            max_new_tokens=max_new_tokens,
            num_beams=num_beams,
            early_stopping=True,
            do_sample=False,
        )
    texts = tokenizer.batch_decode(out_ids, skip_special_tokens=True)
    return [t.strip() for t in texts]


def main() -> None:
    print(f"数据文件: {DATA_PATH}")
    print(f"模型: {MODEL_NAME}")

    try:
        tokenizer, model, device = load_model()
    except ImportError as e:
        raise SystemExit(1) from e
    except Exception as e:
        print(f"详情: {e}")
        raise SystemExit(1) from e

    import torch

    sentences = read_sentences(DATA_PATH)
    print(f"\n{'=' * 14} Transformer 中译英 {'=' * 14}")

    # 逐句生成，便于报告逐条对应；批处理也可，此处保持输出顺序清晰
    for i, zh in enumerate(sentences, 1):
        en = translate_batch(tokenizer, model, device, [zh], max_new_tokens=128, num_beams=4)[0]
        print(f"\n--- 句子 {i} ---")
        print(f"中文: {zh}")
        print(f"英文: {en}")


if __name__ == "__main__":
    main()
