# -*- coding: utf-8 -*-
from __future__ import annotations

import os
import sys
from pathlib import Path

_NLP_ROOT = Path(__file__).resolve().parent.parent
if str(_NLP_ROOT) not in sys.path:
    sys.path.insert(0, str(_NLP_ROOT))
import nlp_runtime

nlp_runtime.setup()

BASE_DIR = Path(__file__).resolve().parent
DATA_PATH = BASE_DIR / "exp-10.1-data.txt"
QA_MODEL = os.environ.get(
    "NLP_WEEK10_QA_MODEL",
    "uer/roberta-base-chinese-extractive-qa",
)


def parse_data(path: Path) -> dict[str, str | list[str]]:
    ctx, qs, ctx_ext, qs_ext = "", [], "", []
    mode = None
    for raw in path.read_text(encoding="utf-8-sig").splitlines():
        line = raw.strip()
        if not line:
            continue
        if line == "[上下文]":
            mode = "ctx"
            continue
        if line == "[问题]":
            mode = "q"
            continue
        if line == "[上下文_扩展]":
            mode = "ctx_ext"
            continue
        if line == "[问题_扩展]":
            mode = "q_ext"
            continue
        if mode == "ctx":
            ctx = line if not ctx else ctx + " " + line
        elif mode == "q":
            qs.append(line)
        elif mode == "ctx_ext":
            ctx_ext = line if not ctx_ext else ctx_ext + " " + line
        elif mode == "q_ext":
            qs_ext.append(line)
    return {"ctx": ctx, "qs": qs, "ctx_ext": ctx_ext, "qs_ext": qs_ext}


def build_qa_model():
    import torch
    from transformers import AutoModelForQuestionAnswering, AutoTokenizer

    token = nlp_runtime.hub_token()
    kw = {"trust_remote_code": True}
    if token:
        kw["token"] = token
    local_path = nlp_runtime.download_model(QA_MODEL)
    print(f"模型目录: {local_path}")
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    tok = AutoTokenizer.from_pretrained(local_path, **kw)
    model = AutoModelForQuestionAnswering.from_pretrained(local_path, **kw)
    model.to(device)
    model.eval()
    return tok, model, device


def predict_qa(tok, model, device, question: str, context: str) -> dict:
    import torch

    enc = tok(
        question,
        context,
        max_length=512,
        truncation="only_second",
        return_tensors="pt",
        return_offsets_mapping=True,
    )
    offset = enc.pop("offset_mapping")[0].tolist()
    input_ids = enc["input_ids"][0]
    seq_type = enc.get("token_type_ids")
    if seq_type is not None:
        seq_type = seq_type[0].tolist()
    valid = []
    for i, (cs, ce) in enumerate(offset):
        if cs == 0 and ce == 0:
            valid.append(False)
        elif seq_type is not None and seq_type[i] == 0:
            valid.append(False)
        else:
            valid.append(True)
    enc = {k: v.to(device) for k, v in enc.items()}
    with torch.inference_mode():
        out = model(**enc)
    start_logits = out.start_logits[0]
    end_logits = out.end_logits[0]
    best_score = float("-inf")
    start_idx = end_idx = 0
    max_len = 32
    for s in range(len(valid)):
        if not valid[s]:
            continue
        e_upper = min(s + max_len, len(valid))
        for e in range(s, e_upper):
            if not valid[e]:
                continue
            score = float(start_logits[s] + end_logits[e])
            if score > best_score:
                best_score = score
                start_idx, end_idx = s, e
    answer = tok.decode(input_ids[start_idx : end_idx + 1], skip_special_tokens=True).strip()
    answer = answer.replace(" ", "")
    char_start = offset[start_idx][0] if start_idx < len(offset) else -1
    char_end = offset[end_idx][1] if end_idx < len(offset) else -1
    return {"answer": answer, "score": best_score, "start": char_start, "end": char_end}


def run_qa(tok, model, device, title: str, context: str, questions: list[str]) -> None:
    if not context or not questions:
        return
    print(f"\n--- {title} ---")
    print(f"上下文: {context}")
    for i, q in enumerate(questions, 1):
        r = predict_qa(tok, model, device, q, context)
        ans = r["answer"] or "（空）"
        print(f"[{i}] 问题: {q}")
        print(f"    答案: {ans}  score={r['score']:.6f}  span={r['start']}-{r['end']}")


def main() -> None:
    print(f"数据文件: {DATA_PATH}")
    print(f"模型: {QA_MODEL}")
    nlp_runtime.print_runtime_info()

    if not DATA_PATH.is_file():
        print("数据文件不存在。")
        raise SystemExit(1)

    data = parse_data(DATA_PATH)
    try:
        tok, model, device = build_qa_model()
    except Exception as e:
        print(f"模型加载失败: {type(e).__name__}: {e}")
        print("提示: 请确认代理已开启；所有下载与临时文件应位于 HF_HOME 与 TMP 所示目录。")
        print("      C 盘旧目录 %USERPROFILE%\\.cache\\huggingface 可手动删除释放空间。")
        raise SystemExit(1) from e

    run_qa(tok, model, device, "任务书上下文与问题", str(data["ctx"]), list(data["qs"]))
    if data["ctx_ext"] and data["qs_ext"]:
        run_qa(tok, model, device, "扩展上下文对比", str(data["ctx_ext"]), list(data["qs_ext"]))


if __name__ == "__main__":
    main()
