# -*- coding: utf-8 -*-
from pathlib import Path

import torch

DATA_PATH = r"./exp-6.2-data.txt"

# BERT 多语言情感（星级 1-5，属于在 BERT 编码器上微调的下游分类模型）
BERT_SENTIMENT_MODEL = "nlptown/bert-base-multilingual-uncased-sentiment"
# 中文因果语言模型续写
GPT2_CHINESE_MODEL = "uer/gpt2-chinese-cluecorpussmall"


def parse_data_file(path):
    text = Path(path).read_text(encoding="utf-8")
    cls_lines, gen_prefix = [], ""
    mode = None
    for raw in text.splitlines():
        line = raw.strip()
        if not line:
            continue
        if line == "[分类]":
            mode = "cls"
            continue
        if line == "[续写前缀]":
            mode = "gen"
            continue
        if mode == "cls":
            cls_lines.append(line)
        elif mode == "gen":
            gen_prefix = line
    return cls_lines, gen_prefix


def load_sections_fallback(path):
    lines = [ln.strip() for ln in Path(path).read_text(encoding="utf-8").splitlines() if ln.strip()]
    if not lines:
        return [], ""
    return lines[:-1], lines[-1]


def build_sentiment_pipeline():
    from transformers import pipeline

    device = 0 if torch.cuda.is_available() else -1
    return pipeline(
        "sentiment-analysis",
        model=BERT_SENTIMENT_MODEL,
        tokenizer=BERT_SENTIMENT_MODEL,
        device=device,
    )


def decode_zh_causal(tokenizer, ids_1d):
    """
    uer/gpt2-chinese 等常用 BertTokenizer，decode 易在汉字之间插入空格。
    这里用 convert_ids_to_tokens 再直接拼接，并跳过 pad、eos、CLS、SEP 等。
    """
    skip = {"[CLS]", "[SEP]", "<|endoftext|>"}
    if tokenizer.pad_token:
        skip.add(tokenizer.pad_token)
    if tokenizer.eos_token:
        skip.add(tokenizer.eos_token)
    for s in tokenizer.all_special_tokens or []:
        skip.add(s)

    ids_list = ids_1d.tolist() if hasattr(ids_1d, "tolist") else list(ids_1d)
    toks = tokenizer.convert_ids_to_tokens(ids_list)
    parts = []
    for t in toks:
        if not t:
            continue
        if tokenizer.eos_token and t == tokenizer.eos_token:
            break
        if t in skip:
            continue
        if t.startswith("##"):
            parts.append(t[2:])
        else:
            parts.append(t)
    return "".join(parts)


def run_sentiment_batch(clf, title, sentences):
    if not sentences:
        return
    print(f"\n--- {title} ---")
    for s in sentences:
        r = clf(s[:512])[0]
        label = r.get("label", "")
        score = float(r.get("score", 0.0))
        print(f"  输入: {s}")
        print(f"  输出: label={label}  score={score:.6f}")


def run_gpt2_generate(prefix, max_new_tokens=40):
    from transformers import AutoModelForCausalLM, AutoTokenizer

    print("\n--- 中文 GPT2 续写 ---")
    print(f"模型: {GPT2_CHINESE_MODEL}")
    tok = AutoTokenizer.from_pretrained(GPT2_CHINESE_MODEL, trust_remote_code=True)
    model = AutoModelForCausalLM.from_pretrained(GPT2_CHINESE_MODEL, trust_remote_code=True)

    # 因果 LM 不应加 Bert 的句首句尾符号；否则会出现 [CLS]…[SEP] 且与训练分布不一致
    cfg_eos = getattr(model.config, "eos_token_id", None)
    cfg_pad = getattr(model.config, "pad_token_id", None)
    eos_id = cfg_eos if cfg_eos is not None else tok.eos_token_id
    if eos_id is None and tok.sep_token_id is not None:
        eos_id = int(tok.sep_token_id)
    pad_id = cfg_pad if cfg_pad is not None else eos_id

    def _id_to_tok_piece(tkz, tid):
        piece = tkz.convert_ids_to_tokens([int(tid)])[0]
        return piece if isinstance(piece, str) else str(piece)

    if eos_id is not None:
        tok.eos_token_id = int(eos_id)
        if tok.eos_token is None:
            tok.eos_token = _id_to_tok_piece(tok, eos_id)
    if pad_id is not None:
        tok.pad_token_id = int(pad_id)
        if tok.pad_token is None:
            tok.pad_token = _id_to_tok_piece(tok, pad_id)
    elif tok.pad_token_id is None and tok.eos_token is not None:
        tok.pad_token = tok.eos_token
    elif tok.pad_token_id is None and tok.eos_token_id is not None:
        tok.pad_token_id = int(tok.eos_token_id)

    gc = getattr(model, "generation_config", None)
    if gc is not None:
        if gc.eos_token_id is None and tok.eos_token_id is not None:
            gc.eos_token_id = int(tok.eos_token_id)
        if gc.pad_token_id is None and tok.pad_token_id is not None:
            gc.pad_token_id = int(tok.pad_token_id)

    model.eval()
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    model.to(device)

    if not prefix:
        print("  （未配置续写前缀，跳过）")
        return

    enc = tok(prefix, return_tensors="pt", add_special_tokens=False)
    enc = {k: v.to(device) for k, v in enc.items()}
    pad_id = tok.pad_token_id
    eos_id = tok.eos_token_id
    if pad_id is None or eos_id is None:
        raise ValueError("tokenizer 缺少 pad_token_id 或 eos_token_id，请检查模型 config 与词表。")
    prompt_len = int(enc["input_ids"].shape[1])
    with torch.no_grad():
        out = model.generate(
            **enc,
            max_new_tokens=max_new_tokens,
            do_sample=True,
            top_k=50,
            top_p=0.92,
            temperature=0.85,
            repetition_penalty=1.25,
            pad_token_id=pad_id,
            eos_token_id=eos_id,
        )
    full_text = decode_zh_causal(tok, out[0])
    new_text = decode_zh_causal(tok, out[0][prompt_len:])
    print(f"  前缀: {prefix}")
    print(f"  解码后整段(无前缀空格伪影): {full_text}")
    print(f"  仅模型续写部分: {new_text}")


def main():
    print(f"数据文件: {DATA_PATH}")
    print(f"情感模型: {BERT_SENTIMENT_MODEL}")
    print("若长时间无法下载，请检查网络，或设置环境变量 HF_ENDPOINT 使用镜像站点。")

    raw = Path(DATA_PATH).read_text(encoding="utf-8")
    if "[分类]" in raw and "[续写前缀]" in raw:
        cls_lines, gen_prefix = parse_data_file(DATA_PATH)
    else:
        cls_lines, gen_prefix = load_sections_fallback(DATA_PATH)

    extra = [
        "服务态度不错，还会再来。",
        "排队两小时，体验非常糟糕。",
    ]

    try:
        clf = build_sentiment_pipeline()
    except Exception as exc:
        print("\n情感 pipeline 初始化失败，以下为常见原因与处理建议。")
        print(f"异常类型: {type(exc).__name__}  信息: {exc}")
        print("可尝试设置环境变量 HF_ENDPOINT=https://hf-mirror.com 或在可联网环境重新运行。")
        clf = None

    if clf is not None:
        run_sentiment_batch(clf, "BERT 多语言情感分类（任务书示例与数据文件）", cls_lines)
        run_sentiment_batch(clf, "改变输入后的对比（任务书步骤 6）", extra)

    try:
        run_gpt2_generate(gen_prefix)
    except Exception as exc:
        print("\n中文 GPT2 加载或生成失败。")
        print(f"异常类型: {type(exc).__name__}  信息: {exc}")
        print("可尝试设置镜像或更换网络后重试。")


if __name__ == "__main__":
    main()
