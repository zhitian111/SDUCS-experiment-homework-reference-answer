# -*- coding: utf-8 -*-
import stanza
from nltk import Tree
from collections import Counter, defaultdict

data_path = r"./exp-3.1-data.txt"

# 读取全部句子
with open(data_path, "r", encoding="utf-8") as f:
    sentences = [line.strip() for line in f if line.strip()]

# 初始化（constituency 依赖 pos）
stanza.download("zh-hans", processors="tokenize,pos,constituency", verbose=False)
nlp = stanza.Pipeline(
    "zh-hans",
    processors="tokenize,pos,constituency",
    use_gpu=False,
    verbose=False
)

all_productions = []
all_trees = []

print("\n================ 全部句子句法树 ================\n")
for idx, sent in enumerate(sentences, 1):
    doc = nlp(sent)
    tree_str = str(doc.sentences[0].constituency)
    tree = Tree.fromstring(tree_str)

    all_trees.append((sent, tree))
    all_productions.extend(tree.productions())

    print(f"[句子 {idx}] {sent}")
    # 关键：按树形结构打印
    tree.pretty_print(unicodelines=True)
    print("-" * 70)

# CFG：全部规则 + 频次
print("\n================ CFG 规则 ================\n")
rule_counter = Counter(str(p) for p in all_productions)
for i, (rule, cnt) in enumerate(sorted(rule_counter.items()), 1):
    print(f"{i:03d}. {rule}    [count={cnt}]")

# PCFG：全部规则 + 概率
print("\n================ PCFG 规则 ================\n")
lhs_total = defaultdict(int)
for p in all_productions:
    lhs_total[str(p.lhs())] += 1

pcfg_rows = []
for rule, cnt in rule_counter.items():
    lhs = rule.split(" -> ")[0]
    prob = cnt / lhs_total[lhs]
    pcfg_rows.append((rule, cnt, prob))

for i, (rule, cnt, prob) in enumerate(sorted(pcfg_rows, key=lambda x: (x[0])), 1):
    print(f"{i:03d}. {rule}    [count={cnt}, prob={prob:.6f}]")

# 结构组成与差异（每句）
print("\n================ 句子结构组成差异 ================\n")
for idx, (sent, tree) in enumerate(all_trees, 1):
    labels = [t.label() for t in tree.subtrees()]
    c = Counter(labels)
    print(f"[句子 {idx}] {sent}")
    print(
        f"IP={c.get('IP',0)}, NP={c.get('NP',0)}, VP={c.get('VP',0)}, "
        f"CP={c.get('CP',0)}, PP={c.get('PP',0)}, ADJP={c.get('ADJP',0)}, ADVP={c.get('ADVP',0)}"
    )
    print("-" * 70)