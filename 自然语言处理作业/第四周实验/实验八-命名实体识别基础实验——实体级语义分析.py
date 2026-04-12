# -*- coding: utf-8 -*-
import jieba.posseg as pseg

DATA_PATH = r"./exp-4.2-data.txt"

# jieba 词性 → 实体类别说明（常见专名/时间/数词）
TAG_TO_ENTITY = {
    "nr": "人名",
    "ns": "地名",
    "nt": "机构名",
    "nz": "其它专名",
    "t": "时间",
    "m": "数词",
    "eng": "英文专名",
    "x": "字符串/符号",
}


def read_sentences(path):
    with open(path, "r", encoding="utf-8") as f:
        return [line.strip() for line in f if line.strip()]


def extract_entities(sentence):
    """返回 [(词, 词性, 实体类别说明), ...]"""
    out = []
    for word, flag in pseg.cut(sentence):
        if flag in TAG_TO_ENTITY:
            out.append((word, flag, TAG_TO_ENTITY[flag]))
    return out


def print_sentence_ner(idx, sentence):
    print(f"\n=== 句{idx}: {sentence}")
    entities = extract_entities(sentence)
    if not entities:
        print("（未识别到专名类词性实体，可结合报告分析漏识别）")
        return
    print("实体\t词性\t类别")
    for word, flag, desc in entities:
        print(f"{word}\t{flag}\t{desc}")


def main():
    pseg.initialize()
    sentences = read_sentences(DATA_PATH)
    print("================ 命名实体识别（jieba 词性） ================")
    for i, sent in enumerate(sentences, 1):
        print_sentence_ner(i, sent)


if __name__ == "__main__":
    main()
