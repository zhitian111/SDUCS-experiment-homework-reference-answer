# -*- coding: utf-8 -*-
import math

import numpy as np

DATA_PATH = r"./exp-6.1-data.txt"
RNG_SEED = 42
D_MODEL = 16


def softmax(x, axis=-1):
    x = x - np.max(x, axis=axis, keepdims=True)
    e = np.exp(x)
    return e / np.sum(e, axis=axis, keepdims=True)


def read_sentences(path):
    with open(path, "r", encoding="utf-8") as f:
        return [ln.strip() for ln in f if ln.strip()]


def tokenize(sentence):
    s = sentence.strip()
    if not s:
        return []
    if " " in s:
        return [t for t in s.split() if t]
    return list(s)


def stable_token_embeddings(tokens, d_model, seed):
    rows = []
    for t in tokens:
        sub = int(seed) + sum((k + 1) * ord(c) for k, c in enumerate(t))
        rng = np.random.default_rng(sub % (2**32))
        rows.append(rng.normal(size=(d_model,)).astype(np.float64))
    return np.stack(rows, axis=0) * 0.15


def self_attention(tokens, d_model=D_MODEL, seed=RNG_SEED):
    rng = np.random.default_rng(seed)
    n = len(tokens)
    if n == 0:
        raise ValueError("空词序列")

    x = stable_token_embeddings(tokens, d_model, seed)
    wq = rng.normal(size=(d_model, d_model)).astype(np.float64) * 0.1
    wk = rng.normal(size=(d_model, d_model)).astype(np.float64) * 0.1
    wv = rng.normal(size=(d_model, d_model)).astype(np.float64) * 0.1

    q = x @ wq
    k = x @ wk
    v = x @ wv
    scale = math.sqrt(d_model)
    scores = (q @ k.T) / scale
    attn = softmax(scores, axis=-1)
    out = attn @ v
    return attn, out, x


def print_matrix(title, mat, row_labels, col_labels):
    print(f"\n--- {title} ---")
    print("列(作为 key 位置):", "  ".join(col_labels))
    for i, row_label in enumerate(row_labels):
        row = "  ".join(f"{mat[i, j]:.6f}" for j in range(mat.shape[1]))
        print(f"  {row_label}: {row}")


def top_pairs(attn, tokens, top_k=5):
    n = len(tokens)
    pairs = []
    for i in range(n):
        for j in range(n):
            pairs.append((attn[i, j], i, j))
    pairs.sort(reverse=True, key=lambda t: t[0])
    out = []
    seen = set()
    for w, i, j in pairs:
        key = (i, j)
        if key in seen:
            continue
        seen.add(key)
        out.append((w, tokens[i], tokens[j], i, j))
        if len(out) >= top_k:
            break
    return out


def main():
    np.random.seed(RNG_SEED)

    print(f"数据文件: {DATA_PATH}  d_model={D_MODEL}  随机种子={RNG_SEED}")

    sentences = read_sentences(DATA_PATH)
    for si, sent in enumerate(sentences, 1):
        toks = tokenize(sent)
        print(f"\n{'=' * 12} 句子 {si} {'=' * 12}")
        print(f"原文: {sent}")
        print(f"分词: {' / '.join(toks)}")

        attn, out, emb = self_attention(toks, d_model=D_MODEL, seed=RNG_SEED + si)
        print_matrix("注意力权重矩阵（行: query 词，列: key 词）", attn, toks, toks)
        print("\n--- 每个 query 词对应的输出向量范数 ---")
        for t, row in zip(toks, out):
            print(f"  {t}: L2={np.linalg.norm(row):.6f}")

        print("\n--- 按权重从高到低的前若干词对（query 行对 key 列）---")
        for rank, (w, q_tok, k_tok, i, j) in enumerate(
            top_pairs(attn, toks, top_k=min(8, len(toks) * len(toks))), 1
        ):
            print(f"  {rank}. query={q_tok} 对 key={k_tok} 权重={w:.6f}  (i={i}, j={j})")


if __name__ == "__main__":
    main()
