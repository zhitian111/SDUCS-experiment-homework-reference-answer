from __future__ import annotations

import re
from pathlib import Path

DATA_PATH = r"./exp-7.2-data.txt"


def init_jieba() -> bool:
    """在部分 Python 版本组合下 jieba 可能因 pkg_resources 等问题无法导入，此时仍可进行规则抽取。"""
    try:
        import jieba

        jieba.initialize()
        return True
    except Exception:
        return False


JIEBA_OK = init_jieba()


def parse_data_file(path: str) -> tuple[list[str], str]:
    events: list[str] = []
    integrated = ""
    mode = None
    for raw in Path(path).read_text(encoding="utf-8").splitlines():
        line = raw.strip()
        if not line:
            continue
        if line == "[事件句]":
            mode = "evt"
            continue
        if line == "[综合抽取]":
            mode = "int"
            continue
        if mode == "evt":
            events.append(line)
        elif mode == "int":
            integrated = line
    return events, integrated


def tokenize_hint(sentence: str) -> str:
    if not JIEBA_OK:
        return "（jieba 不可用，已跳过分词参考。任务书环境为 Python3.8+，一般可正常 pip install jieba。）"
    import jieba.posseg as pseg

    pairs = list(pseg.cut(sentence))
    return "  ".join(f"{w}/{f}" for w, f in pairs)


def strip_punct_end(s: str) -> str:
    return s.strip().rstrip("。.!！?？")


def extract_time_prefix(sentence: str) -> tuple[str, str]:
    m = re.match(r"^(\d{4}\s*年\s*\d{1,2}\s*月\s*\d{1,2}\s*日)\s*[，,]\s*(.+)$", sentence.strip())
    if not m:
        return "", sentence.strip()
    t = re.sub(r"\s+", "", m.group(1))
    rest = m.group(2).strip()
    return t, rest


def extract_event_structure(sentence: str) -> dict:
    """
    返回字典字段与任务书「主体、事件、客体、时间、地点」对齐。
    未抽到的键对应空字符串，便于统一制表打印。
    """
    s0 = strip_punct_end(sentence)
    time, core = extract_time_prefix(s0)
    if not time:
        core = s0

    subj = obj = loc = ""
    trigger = ""
    note = ""

    m = re.match(r"^(.+?)发布了(.+)$", core)
    if m:
        subj, obj = m.group(1).strip(), m.group(2).strip()
        trigger = "发布"
        return _result(time, subj, trigger, obj, loc, note)

    m = re.match(r"^(.+?)创立了(.+)$", core)
    if m:
        subj, obj = m.group(1).strip(), m.group(2).strip()
        trigger = "创立"
        return _result(time, subj, trigger, obj, loc, note)

    m = re.match(r"^(.+?)在(.+?)参加(?:了)?(.+)$", core)
    if m:
        subj, loc, obj = m.group(1).strip(), m.group(2).strip(), m.group(3).strip()
        trigger = "参加"
        return _result(time, subj, trigger, obj, loc, note)

    m = re.match(r"^(.+?)在(.+?)开会$", core)
    if m:
        subj, loc = m.group(1).strip(), m.group(2).strip()
        trigger = "开会"
        return _result(time, subj, trigger, obj, loc, note)

    m = re.match(r"^(.+?)买了(.+)$", core)
    if m:
        subj, obj = m.group(1).strip(), m.group(2).strip()
        trigger = "买"
        return _result(time, subj, trigger, obj, loc, note)

    note = "未命中规则模板，请在本机用更复杂句法或深度学习模型扩展。"
    return _result(time, subj, trigger, obj, loc, note)


def _result(time: str, subj: str, trigger: str, obj: str, loc: str, note: str) -> dict:
    return {
        "时间": time,
        "主体": subj,
        "事件触发词": trigger,
        "客体": obj,
        "地点": loc,
        "备注": note,
    }


def is_complete(ev: dict) -> str:
    need = ["主体", "事件触发词"]
    ok = all(ev.get(k) for k in need)
    if ok and ev.get("事件触发词") in ("发布", "创立", "买"):
        ok = ok and bool(ev.get("客体"))
    if ok and ev.get("事件触发词") == "参加":
        ok = ok and bool(ev.get("客体")) and bool(ev.get("地点"))
    if ok and ev.get("事件触发词") == "开会":
        ok = ok and bool(ev.get("地点"))
    return "结构较完整" if ok else "结构不完整（缺少关键槽位）"


def integrated_ie(text: str) -> None:
    """任务书「综合实验」示例输出。"""
    t = strip_punct_end(text)
    print("\n--- 综合信息抽取（任务书给定输入） ---")
    print(f"输入: {text}")

    m = re.match(r"^(.+?)在(.+?)讲授(.+)$", t)
    if not m:
        print("（综合示例未命中规则，请检查数据文件中的句子是否与任务书一致。）")
        return

    who, org, course = m.group(1).strip(), m.group(2).strip(), m.group(3).strip()

    print("\n实体（规则标注，便于与实验十三模型结果对照）:")
    print(f"  {who}（人）")
    print(f"  {org}（机构）")
    print(f"  {course}（课程）")

    print("\n关系（模板化输出，对应任务书示例）:")
    print(f"  ({who}, 任教于, {org})")

    print("\n事件（结构化字典）:")
    ev = {
        "主体": who,
        "行为": "讲授",
        "客体": course,
        "地点": org,
    }
    print(f"  {ev}")

    print("\njieba 分词与词性参考:")
    print(f"  {tokenize_hint(t)}")


def print_event_block(title: str, sentences: list[str]) -> None:
    print(f"\n--- {title} ---")
    print("序号 | 原句 | 时间 | 主体 | 触发词 | 客体 | 地点 | 完整性提示 | 备注")
    print("-" * 96)
    for i, s in enumerate(sentences, 1):
        ev = extract_event_structure(s)
        print(
            f"{i:>2} | {s} | {ev['时间'] or '（无）'} | {ev['主体'] or '（无）'} | "
            f"{ev['事件触发词'] or '（无）'} | {ev['客体'] or '（无）'} | {ev['地点'] or '（无）'} | "
            f"{is_complete(ev)} | {ev['备注']}"
        )
        print(f"    分词参考: {tokenize_hint(s)}")


def main():
    print(f"数据文件: {DATA_PATH}")
    print(f"jieba 分词参考: {'已启用' if JIEBA_OK else '未启用（规则抽取不受影响）'}")

    events, integrated = parse_data_file(DATA_PATH)
    print("\n--- 实验十四 事件抽取：逐句结构化结果（便于报告截图） ---")
    print_event_block("事件句（任务书第五节数据）", events)

    if integrated:
        integrated_ie(integrated)
    else:
        print("\n（数据文件中未找到 [综合抽取] 段落，已跳过综合示例。）")


if __name__ == "__main__":
    main()
