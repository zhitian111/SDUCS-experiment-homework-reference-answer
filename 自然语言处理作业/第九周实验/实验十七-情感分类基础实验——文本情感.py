# -*- coding: utf-8 -*-
from __future__ import annotations

from pathlib import Path

import jieba
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics import accuracy_score
from sklearn.model_selection import LeaveOneOut
from sklearn.naive_bayes import MultinomialNB
from sklearn.pipeline import Pipeline

BASE_DIR = Path(__file__).resolve().parent
DATA_PATH = BASE_DIR / "exp-9.1-data.txt"
TEST_PATH = BASE_DIR / "exp-9.1-test.txt"


def jieba_doc(text: str) -> str:
    return " ".join(jieba.cut(text.strip()))


def read_labeled(path: Path) -> tuple[list[str], list[str]]:
    texts, labels = [], []
    for raw in path.read_text(encoding="utf-8").splitlines():
        line = raw.strip()
        if not line:
            continue
        if "\t" in line:
            sent, lab = line.split("\t", 1)
        else:
            parts = line.rsplit(None, 1)
            if len(parts) != 2:
                continue
            sent, lab = parts[0], parts[1]
        texts.append(sent.strip())
        labels.append(lab.strip())
    return texts, labels


def read_lines(path: Path) -> list[str]:
    if not path.is_file():
        return []
    return [ln.strip() for ln in path.read_text(encoding="utf-8").splitlines() if ln.strip()]


def build_clf() -> Pipeline:
    return Pipeline(
        [
            (
                "tfidf",
                TfidfVectorizer(
                    analyzer=lambda doc: doc.split(),
                    min_df=1,
                ),
            ),
            ("nb", MultinomialNB()),
        ]
    )


def main() -> None:
    print(f"训练数据: {DATA_PATH}")
    print(f"测试数据: {TEST_PATH}")

    train_x, train_y = read_labeled(DATA_PATH)
    if not train_x:
        print("训练数据为空。")
        return

    train_corpus = [jieba_doc(s) for s in train_x]
    clf = build_clf()
    clf.fit(train_corpus, train_y)

    print("\n--- 训练集预测 ---")
    pred_train = clf.predict(train_corpus)
    for sent, gold, pred in zip(train_x, train_y, pred_train):
        mark = "OK" if gold == pred else "ERR"
        print(f"{mark} | 原句: {sent} | 标签: {gold} | 预测: {pred}")

    print(f"\n训练集准确率: {accuracy_score(train_y, pred_train):.4f}")

    print("\n--- 留一法交叉验证 ---")
    loo = LeaveOneOut()
    loo_true, loo_pred = [], []
    for tr_idx, te_idx in loo.split(train_corpus):
        x_tr = [train_corpus[i] for i in tr_idx]
        y_tr = [train_y[i] for i in tr_idx]
        x_te = train_corpus[te_idx[0]]
        y_te = train_y[te_idx[0]]
        m = build_clf()
        m.fit(x_tr, y_tr)
        p = m.predict([x_te])[0]
        loo_true.append(y_te)
        loo_pred.append(p)
        print(f"留出: {train_x[te_idx[0]]} | 真实: {y_te} | 预测: {p}")
    print(f"留一法准确率: {accuracy_score(loo_true, loo_pred):.4f}")

    test_sents = read_lines(TEST_PATH)
    if test_sents:
        print("\n--- 测试句预测 ---")
        test_corpus = [jieba_doc(s) for s in test_sents]
        pred_test = clf.predict(test_corpus)
        for sent, pred in zip(test_sents, pred_test):
            print(f"原句: {sent} | 预测: {pred}")

    vocab = clf.named_steps["tfidf"].get_feature_names_out()
    print(f"\n特征维度: {len(vocab)}")
    if len(vocab) <= 80:
        print("词表:", " ".join(vocab))


if __name__ == "__main__":
    main()
