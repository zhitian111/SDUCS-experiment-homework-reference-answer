# -*- coding: utf-8 -*-
import spacy

MODEL = "zh_core_web_sm"
DATA_PATH = r"./exp-3.2-data.txt"


def read_sentences(path):
    with open(path, "r", encoding="utf-8") as f:
        return [line.strip() for line in f if line.strip()]


def print_dep_table(doc):
    # id, 词, head_id(0表示ROOT), head词, dep
    for t in doc:
        head_id = 0 if t.dep_ == "ROOT" else (t.head.i + 1)
        print(f"{t.i + 1}\t{t.text}\t{head_id}\t{t.head.text}\t{t.dep_}")


def print_dep_tree(doc):
    roots = [t for t in doc if t.dep_ == "ROOT"]

    def walk(node, depth=0):
        indent = "  " * depth
        rel = "ROOT" if depth == 0 else node.dep_
        print(f"{indent}{node.text} [{rel}]")
        for c in sorted(node.children, key=lambda x: x.i):
            walk(c, depth + 1)

    for r in roots:
        walk(r)


def print_svo(doc):
    root = [t for t in doc if t.dep_ == "ROOT"][0]
    subj = [t.text for t in root.children if "subj" in t.dep_ or t.dep_ == "nsubj"]
    obj = [t.text for t in root.children if "obj" in t.dep_ or t.dep_ in ("dobj", "obj", "iobj")]
    parts = [f"谓语/根:{root.text}"]
    if subj:
        parts.append("主语:" + " ".join(subj))
    if obj:
        parts.append("宾语:" + " ".join(obj))
    print(" | ".join(parts))


def main():
    nlp = spacy.load(MODEL)
    sentences = read_sentences(DATA_PATH)

    for i, sent in enumerate(sentences, 1):
        doc = nlp(sent)
        print(f"\n=== 句{i}: {sent}")
        print("id\tword\thead_id\thead\tdep")
        print_dep_table(doc)
        print("--- tree ---")
        print_dep_tree(doc)
        print("--- svo ---")
        print_svo(doc)


if __name__ == "__main__":
    main()