import random
import re

import jieba
import numpy as np
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity

DATA_PATH = r"./exp-5.1-data.txt"
RNG_SEED = 42


def read_paragraphs(path):
    """按空行分段，每段为有序句子列表（一句一行）。"""
    with open(path, "r", encoding="utf-8") as f:
        raw = f.read()
    blocks = re.split(r"\n\s*\n", raw.strip())
    paragraphs = []
    for block in blocks:
        lines = [ln.strip() for ln in block.splitlines() if ln.strip()]
        if lines:
            paragraphs.append(lines)
    return paragraphs


def sentence_to_tfidf_doc(sentence):
    return " ".join(jieba.lcut(sentence))


def adjacent_pair_similarities(sentences):
    """相邻句 TF-IDF 余弦相似度列表；单句返回空列表。"""
    if len(sentences) < 2:
        return []
    docs = [sentence_to_tfidf_doc(s) for s in sentences]
    # 已用 jieba 按词空格拼接；默认 token_pattern 要求长度>=2，会丢掉「他」「了」等单字，
    # 导致相邻句几乎无共现词、余弦恒为 0。按空格切分即保留 jieba 词元。
    vec = TfidfVectorizer(analyzer=lambda s: s.split())
    mat = vec.fit_transform(docs)
    sims = []
    for i in range(len(sentences) - 1):
        a = mat[i : i + 1]
        b = mat[i + 1 : i + 2]
        sims.append(float(cosine_similarity(a, b)[0, 0]))
    return sims


def mean_or_none(values):
    if not values:
        return None
    return float(np.mean(values))


def print_analysis(title, sentences, sims):
    print(f"\n--- {title} ---")
    for i, s in enumerate(sentences, 1):
        print(f"  [{i}] {s}")
    if not sims:
        print("  （少于两句，无相邻句相似度）")
        return
    print("  相邻句余弦相似度:")
    for i, sim in enumerate(sims, 1):
        print(f"    句{i}—句{i + 1}: {sim:.6f}")
    print(f"  平均分: {mean_or_none(sims):.6f}")


def heuristic_verdict(orig_mean, shuf_mean):
    if orig_mean is None or shuf_mean is None:
        return "样本过短，无法比较。"
    if orig_mean > shuf_mean:
        return (
            "原序相邻句相似度平均更高，在该启发式下更倾向判断为「更连贯」；"
            "相似度仅为辅助指标，不能覆盖所有语篇现象。"
        )
    if orig_mean < shuf_mean:
        return (
            "乱序平均分不低于原序：说明仅靠词重叠/相邻相似度不足以刻画连贯性，"
            "需结合因果、时序等更高层信息。"
        )
    return "两者平均分接近，需结合更多线索判断连贯性。"


def main():
    random.seed(RNG_SEED)
    paragraphs = read_paragraphs(DATA_PATH)
    print("================ 篇章连贯性：相邻句 TF-IDF 相似度 ================")
    print(f"数据文件: {DATA_PATH}  随机种子(乱序): {RNG_SEED}")

    for pi, orig in enumerate(paragraphs, 1):
        print(f"\n{'=' * 16} 段落 {pi} {'=' * 16}")
        shuffled = orig[:]
        random.shuffle(shuffled)

        orig_sims = adjacent_pair_similarities(orig)
        shuf_sims = adjacent_pair_similarities(shuffled)

        print_analysis("原序（连贯）", orig, orig_sims)
        print_analysis("乱序（打乱）", shuffled, shuf_sims)

        om = mean_or_none(orig_sims)
        sm = mean_or_none(shuf_sims)
        print("\n--- 对比结论（启发式） ---")
        if om is not None and sm is not None:
            print(f"  原序平均分: {om:.6f}  乱序平均分: {sm:.6f}")
        print(f"  {heuristic_verdict(om, sm)}")


if __name__ == "__main__":
    main()
