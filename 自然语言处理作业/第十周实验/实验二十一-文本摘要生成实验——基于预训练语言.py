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
DATA_PATH = BASE_DIR / "exp-10.2-data.txt"
SUM_MODEL = os.environ.get("NLP_WEEK10_SUM_MODEL", "fnlp/bart-base-chinese")

MAX_LEN_LONG = int(os.environ.get("NLP_WEEK10_SUM_MAX_LEN", "64"))
MAX_LEN_SHORT = int(os.environ.get("NLP_WEEK10_SUM_MAX_LEN_SHORT", "24"))


def parse_data(path: Path) -> dict[str, str]:
    blocks: dict[str, str] = {}
    mode = None
    buf: list[str] = []
    for raw in path.read_text(encoding="utf-8-sig").splitlines():
        line = raw.strip()
        if line.startswith("[") and line.endswith("]"):
            if mode and buf:
                blocks[mode] = "".join(buf)
            mode = line[1:-1]
            buf = []
            continue
        if mode and line:
            buf.append(line)
    if mode and buf:
        blocks[mode] = "".join(buf)
    return blocks


def build_sum_model():
    import torch
    from transformers import AutoModelForSeq2SeqLM, AutoTokenizer

    token = nlp_runtime.hub_token()
    kw = {"trust_remote_code": True}
    if token:
        kw["token"] = token
    local_path = nlp_runtime.download_model(SUM_MODEL)
    print(f"模型目录: {local_path}")
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    tok = AutoTokenizer.from_pretrained(local_path, **kw)
    model = AutoModelForSeq2SeqLM.from_pretrained(local_path, **kw)
    model.to(device)
    model.eval()
    return tok, model, device


def gen_summary(tok, model, device, text: str, max_length: int, min_length: int = 8) -> str:
    import torch

    inputs = tok(text[:1024], return_tensors="pt", truncation=True, max_length=512)
    gen_in = {k: v.to(device) for k, v in inputs.items() if k in ("input_ids", "attention_mask")}
    with torch.inference_mode():
        out_ids = model.generate(
            **gen_in,
            max_length=max_length,
            min_length=min_length,
            num_beams=4,
            early_stopping=True,
        )
    return tok.decode(out_ids[0], skip_special_tokens=True).strip().replace(" ", "")


def summarize(tok, model, device, title: str, text: str, max_length: int, min_length: int = 8) -> None:
    if not text:
        return
    print(f"\n--- {title} ---")
    print(f"原文({len(text)}字): {text}")
    summary = gen_summary(tok, model, device, text, max_length, min_length)
    print(f"摘要({len(summary)}字, max_length={max_length}): {summary}")


def main() -> None:
    print(f"数据文件: {DATA_PATH}")
    print(f"模型: {SUM_MODEL}")
    nlp_runtime.print_runtime_info()

    if not DATA_PATH.is_file():
        print("数据文件不存在。")
        raise SystemExit(1)

    blocks = parse_data(DATA_PATH)
    try:
        tok, model, device = build_sum_model()
    except Exception as e:
        print(f"模型加载失败: {type(e).__name__}: {e}")
        print("提示: 请确认代理已开启；所有下载与临时文件应位于 HF_HOME 与 TMP 所示目录。")
        print("      C 盘旧目录 %USERPROFILE%\\.cache\\huggingface 可手动删除释放空间。")
        print("      也可双击运行: 配置代理并运行第十周实验.bat 21")
        raise SystemExit(1) from e

    t1 = blocks.get("文本一", "")
    t2 = blocks.get("文本二", "")
    t_short = blocks.get("短文本", "")

    if t1:
        summarize(tok, model, device, "文本一", t1, MAX_LEN_LONG)
    if t2:
        summarize(tok, model, device, "文本二", t2, MAX_LEN_LONG)
    if t_short:
        summarize(tok, model, device, "短文本", t_short, MAX_LEN_LONG)
        summarize(tok, model, device, "短文本（较短 max_length）", t_short, MAX_LEN_SHORT)


if __name__ == "__main__":
    main()
