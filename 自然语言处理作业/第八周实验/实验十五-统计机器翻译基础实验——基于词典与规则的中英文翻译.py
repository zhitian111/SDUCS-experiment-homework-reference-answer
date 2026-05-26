from __future__ import annotations

from pathlib import Path

import jieba

BASE_DIR = Path(__file__).resolve().parent
DATA_PATH = BASE_DIR / "exp-8.1-data.txt"

# 任务书示例词典（键为中文词或短语，值为英文；多字短语优先于单字）
ZH_EN_DICT: dict[str, str] = {
    "我": "I",
    "你": "You",
    "爱": "Love",
    "学习": "Study",
    "自然语言处理": "NLP",
    "苹果": "Apple",
}

DEFAULT_SENTENCES = [
    "我爱自然语言处理。",
    "你学习人工智能。",
    "我爱苹果。",
]


def register_dict_for_jieba() -> None:
    """将词典中的词组注册到 jieba，减少多字词条被错误切开的情况。"""
    for phrase in sorted(ZH_EN_DICT.keys(), key=len, reverse=True):
        jieba.add_word(phrase, freq=10**9)


def read_sentences(path: Path) -> list[str]:
    if not path.is_file():
        return list(DEFAULT_SENTENCES)
    out: list[str] = []
    for raw in path.read_text(encoding="utf-8").splitlines():
        s = raw.strip()
        if s:
            out.append(s)
    return out if out else list(DEFAULT_SENTENCES)


def translate_sentence(sentence: str, unk_template: str = "[未登录:{word}]") -> tuple[str, list[str], list[str]]:
    """
    分词后逐词查表并顺序拼接英文（不做句法调序）。

    返回: (英文串, 分词列表, 各片段对应的英文或占位说明)
    """
    tokens = list(jieba.cut(sentence.strip()))
    pieces: list[str] = []
    en_parts: list[str] = []
    for tok in tokens:
        if tok.strip() == "":
            continue
        # 纯标点原样略过或保留：此处跳过空白与常见句末标点，便于阅读
        if all(not ch.isalnum() and ch not in ZH_EN_DICT for ch in tok):
            continue
        en = ZH_EN_DICT.get(tok)
        if en is None:
            en = unk_template.format(word=tok)
        pieces.append(tok)
        en_parts.append(en)
    return " ".join(en_parts), pieces, en_parts


def main() -> None:
    register_dict_for_jieba()

    print(f"数据文件: {DATA_PATH}")
    print(f"词典条目数: {len(ZH_EN_DICT)}")
    print("\n--- 当前中英词典（中文 -> 英文）---")
    for zh in sorted(ZH_EN_DICT.keys(), key=lambda s: (-len(s), s)):
        print(f"  {zh} -> {ZH_EN_DICT[zh]}")

    sentences = read_sentences(DATA_PATH)
    print(f"\n{'=' * 14} 翻译结果 {'=' * 14}")

    for i, sent in enumerate(sentences, 1):
        en_line, toks, en_tok = translate_sentence(sent)
        print(f"\n--- 句子 {i} ---")
        print(f"原文: {sent}")
        print(f"jieba 分词: {' / '.join(toks)}")
        print(f"逐词译文片段: {' | '.join(en_tok)}")
        print(f"组合英文: {en_line}")


if __name__ == "__main__":
    main()
