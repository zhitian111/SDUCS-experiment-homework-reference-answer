# -*- coding: utf-8 -*-
import os
from pathlib import Path

import jieba
import numpy as np
from gensim.models import KeyedVectors, Word2Vec
from sklearn.metrics.pairwise import cosine_similarity

PRETRAINED_W2V_PATH = os.environ.get("PRETRAINED_W2V_PATH", "./pretrained-zh.w2v.txt")
PAIRS_PATH = r"./exp-4.1-data.txt"
CORPUS_PATH = r"./exp-4.1-corpus.txt"


def load_word_pairs(path):
    pairs = []
    with open(path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            parts = line.split()
            if len(parts) >= 2:
                pairs.append((parts[0], parts[1]))
    return pairs


def load_corpus_lines(path):
    with open(path, "r", encoding="utf-8") as f:
        return [line.strip() for line in f if line.strip()]


def tokenize_corpus(sentences):
    return [list(jieba.cut(s)) for s in sentences]


def load_or_build_keyed_vectors():
    p = Path(PRETRAINED_W2V_PATH)
    if p.is_file():
        print(f"加载预训练词向量: {p}")
        if p.suffix.lower() == ".kv":
            return KeyedVectors.load(str(p))
        for binary in (False, True):
            try:
                return KeyedVectors.load_word2vec_format(
                    str(p),
                    binary=binary,
                    encoding="utf-8",
                    unicode_errors="ignore",
                )
            except Exception:
                continue
        raise RuntimeError(f"无法解析词向量文件: {p}")

    print(f"未找到预训练文件 {p}，使用语料训练 Word2Vec: {CORPUS_PATH}")
    sents = load_corpus_lines(CORPUS_PATH)
    if not sents:
        raise FileNotFoundError(f"语料为空: {CORPUS_PATH}")
    tokenized = tokenize_corpus(sents)
    model = Word2Vec(
        sentences=tokenized,
        vector_size=100,
        window=5,
        min_count=1,
        workers=4,
        sg=1,
        epochs=80,
        seed=42,
    )
    return model.wv


def get_vector(kv, word):
    if word not in kv:
        return None
    return np.asarray(kv[word], dtype=np.float64)


def cosine_sim_vec(a, b):
    if a is None or b is None:
        return None
    a2 = a.reshape(1, -1)
    b2 = b.reshape(1, -1)
    return float(cosine_similarity(a2, b2)[0, 0])


def main():
    kv = load_or_build_keyed_vectors()
    pairs = load_word_pairs(PAIRS_PATH)

    rows = []
    print("\n================ 词对余弦相似度 ================\n")
    for w1, w2 in pairs:
        v1, v2 = get_vector(kv, w1), get_vector(kv, w2)
        sim = cosine_sim_vec(v1, v2)
        if sim is None:
            msg = "（存在未登录词，无法计算）"
            rows.append((w1, w2, None, msg))
            print(f"{w1} — {w2}\t{msg}")
        else:
            rows.append((w1, w2, sim, ""))
            print(f"{w1} — {w2}\t余弦相似度: {sim:.6f}")

    valid = [(a, b, s) for a, b, s, _ in rows if s is not None]
    if valid:
        print("\n================ 按相似度排序（高 → 低） ================\n")
        for w1, w2, s in sorted(valid, key=lambda x: -x[2]):
            print(f"{s:.6f}\t{w1}\t{w2}")


if __name__ == "__main__":
    main()
