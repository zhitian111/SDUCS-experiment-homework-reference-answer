import logging
import re

import jieba.posseg as pseg

DATA_PATH = r"./exp-5.2-data.txt"

# 任务书常见实体（jieba 可能未标为 nr）
EXTRA_ENTITIES = ("小明", "小红", "老师", "学生")

MALE_LIKE = {"小明", "老师", "学生"}
FEMALE_LIKE = {"小红"}

SENT_SPLIT = re.compile(r"[。！？；]+")


def read_documents(path):
    with open(path, "r", encoding="utf-8") as f:
        return [ln.strip() for ln in f if ln.strip()]


def split_sentences_with_offsets(text):
    """返回 [(句文本, 句在全文中的起始下标), ...]，下标与 merge_entity_spans 一致。"""
    text = text.strip()
    out = []
    start = 0
    for m in re.finditer(r"[。！？；]+", text):
        raw = text[start : m.start()]
        if raw.strip():
            lead = len(raw) - len(raw.lstrip())
            s_begin = start + lead
            out.append((raw.strip(), s_begin))
        start = m.end()
    raw = text[start:]
    if raw.strip():
        lead = len(raw) - len(raw.lstrip())
        out.append((raw.strip(), start + lead))
    return out


def find_extra_entities(text):
    """按最长优先扫描，避免重叠重复。"""
    found = []
    i = 0
    n = len(text)
    sorted_extra = sorted(EXTRA_ENTITIES, key=len, reverse=True)
    while i < n:
        matched = None
        for w in sorted_extra:
            if text.startswith(w, i):
                matched = w
                break
        if matched:
            found.append((i, i + len(matched), matched))
            i += len(matched)
        else:
            i += 1
    return found


def find_nr_spans(text):
    spans = []
    for word, flag in pseg.cut(text):
        if flag != "nr" or not word.strip():
            continue
        start = 0
        while True:
            idx = text.find(word, start)
            if idx < 0:
                break
            spans.append((idx, idx + len(word), word))
            start = idx + 1
    return spans


def merge_entity_spans(text):
    """合并 jieba nr 与补充词表，去重叠（优先较长 span）。"""
    spans = find_nr_spans(text) + find_extra_entities(text)
    spans.sort(key=lambda x: (x[0], -(x[1] - x[0])))
    merged = []
    for s, e, w in spans:
        if any(not (e <= ms or s >= me) for ms, me, _ in merged):
            continue
        merged.append((s, e, w))
    merged.sort(key=lambda x: x[0])
    return merged


def pronoun_class(ch):
    if ch == "他":
        return "male"
    if ch == "她":
        return "female"
    if ch == "它":
        return "it"
    return None


def entity_class(word):
    if word in FEMALE_LIKE:
        return "female"
    if word in MALE_LIKE:
        return "male"
    return "male"  # 未登录 nr 默认按「他」类处理（基础实验）


def compatible(pron_cls, ent_cls):
    if pron_cls == "it":
        return ent_cls == "it"
    if pron_cls == "male":
        return ent_cls == "male"
    if pron_cls == "female":
        return ent_cls == "female"
    return False


def find_pronouns(text):
    out = []
    for m in re.finditer(r"[他她它]", text):
        out.append((m.start(), m.end(), m.group()))
    return out


def resolve_pronoun(pron_ch, pron_start, global_spans, sentence_local_text, sent_start):
    """sent_start: 本句在全文中的起始下标；pron_start 为代词在句内下标。"""
    abs_pron = sent_start + pron_start
    prior_entities = []
    for s, e, w in global_spans:
        if e <= abs_pron:
            prior_entities.append(w)

    pcls = pronoun_class(pron_ch)
    gender_ok = [w for w in prior_entities if compatible(pcls, entity_class(w))]

    # 课上示例：「小明告诉小红，他要离开」—— 竞争解读
    sent_abs_end = sent_start + len(sentence_local_text)
    same_sent = [
        w
        for s, e, w in global_spans
        if s >= sent_start and e <= sent_abs_end and e <= abs_pron
    ]
    lesson_ambiguous = (
        pron_ch == "他"
        and "小明" in same_sent
        and "小红" in same_sent
        and len(gender_ok) >= 1
    )

    uniq_gender_ok = list(dict.fromkeys(gender_ok))
    if len(uniq_gender_ok) >= 2:
        return (
            "ambiguous",
            uniq_gender_ok,
            "多个同性实体均可与「{}」匹配".format(pron_ch),
        )
    if lesson_ambiguous:
        return "ambiguous", ["小明", "小红"], "主从句主语省略时的竞争（课堂讨论：语法上「他」多指男性实体）"
    if len(gender_ok) == 1:
        return "resolved", [gender_ok[-1]], None
    if len(gender_ok) == 0:
        return "unresolved", [], "前文无匹配性别的实体"
    return "unresolved", [], ""


def process_document(doc_idx, text):
    print(f"\n=== 短文 {doc_idx} ===\n全文: {text}\n")

    global_spans = merge_entity_spans(text)
    print("实体（nr + 补充词表，位置去重后）:")
    if not global_spans:
        print("  （无）")
    else:
        for s, e, w in global_spans:
            print(f"  [{s}:{e}] {w}  （类别: {entity_class(w)}）")

    sent_spans = split_sentences_with_offsets(text)
    print("\n分句:")
    for i, (s, _) in enumerate(sent_spans, 1):
        print(f"  [{i}] {s}")

    print("\n代词消解（最近匹配 + 性别约束；多候选标歧义）:")
    for si, (sent, sent_start) in enumerate(sent_spans, 1):
        pronouns = find_pronouns(sent)
        for ps, _pe, pch in pronouns:
            status, cands, reason = resolve_pronoun(
                pch, ps, global_spans, sent, sent_start
            )
            rel_start = sent_start + ps
            if status == "resolved":
                print(f"  句{si} 位置{rel_start}: 「{pch}」 → {cands[0]}")
            elif status == "ambiguous":
                print(
                    f"  句{si} 位置{rel_start}: 「{pch}」 歧义，候选: {', '.join(cands)}"
                )
                if reason:
                    print(f"         说明: {reason}")
            else:
                print(f"  句{si} 位置{rel_start}: 「{pch}」 未消解 — {reason}")


def main():
    logging.getLogger("jieba").setLevel(logging.WARNING)
    pseg.initialize()
    docs = read_documents(DATA_PATH)
    print("================ 指代消解（规则 + 性别约束） ================")
    print(f"数据文件: {DATA_PATH}\n")
    for idx, doc in enumerate(docs, 1):
        process_document(idx, doc)


if __name__ == "__main__":
    main()
