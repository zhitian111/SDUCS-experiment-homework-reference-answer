# -*- coding: utf-8 -*-
"""
实验十三：命名实体识别。

默认使用 HuggingFace Transformers 的 NER pipeline，底层为 PyTorch（与任务书「transformers 推荐」一致，无需 TensorFlow）。
可选：设置环境变量 NLP_WEEK7_TRY_HANLP_FIRST=1 时优先尝试 HanLP（部分模型需 pip install "hanlp[full]"）。

依赖（PyTorch 路线，体积远小于 hanlp[full]）:
  pip install torch transformers huggingface_hub
模型名: 环境变量 NLP_WEEK7_NER_MODEL，默认 uer/roberta-base-finetuned-cluener2020-chinese（可为本地目录路径）。

代理: HTTP_PROXY、HTTPS_PROXY。若 pip 报 Errno 28 磁盘满，请把 TEMP、TMP、PIP_CACHE_DIR 指到空间足够的盘符后再装包。
Hub: 若下载阶段长时间无新输出或 Cancellation requested，多为 XET 路径或网络问题；脚本默认 HF_HUB_DISABLE_XET=1（须在首次 import transformers 前生效）。国内可设 HF_ENDPOINT=https://hf-mirror.com。
令牌: 勿把 token 写进代码。任选其一，在运行前设置:
  环境变量 HF_TOKEN 或 HUGGING_FACE_HUB_TOKEN（推荐）
  或 NLP_WEEK7_HF_TOKEN_FILE 指向仅含一行 token 的文本文件路径
  或 NLP_WEEK7_USE_HF_CLI_TOKEN=1 且已 huggingface-cli login，则 pipeline 使用 token=True
在第七周实验目录下运行: python 实验十三-命名实体识别实验——信息抽取基础.py
"""
from __future__ import annotations

import os
import re
from pathlib import Path

# huggingface_hub 会在 import 阶段读取；XET 后端在部分网络下会长时间无进度，看似卡死。
if "HF_HUB_DISABLE_XET" not in os.environ:
    os.environ["HF_HUB_DISABLE_XET"] = "1"
os.environ.setdefault("HF_HUB_DOWNLOAD_TIMEOUT", "600")

DATA_PATH = r"./exp-7.1-data.txt"
HF_NER_MODEL = os.environ.get(
    "NLP_WEEK7_NER_MODEL",
    "uer/roberta-base-finetuned-cluener2020-chinese",
)


def resolve_hf_token() -> tuple[str | None, str]:
    """
    返回 (token, 来源说明)。不把 token 写入日志或打印明文。
    在首次 import transformers / huggingface_hub 之前调用，并写入 os.environ["HF_TOKEN"] 供 Hub 使用。
    """
    for key in ("HF_TOKEN", "HUGGING_FACE_HUB_TOKEN"):
        raw = os.environ.get(key)
        if raw and raw.strip():
            return raw.strip(), f"环境变量 {key}"

    path = os.environ.get("NLP_WEEK7_HF_TOKEN_FILE", "").strip()
    if path:
        p = Path(path).expanduser()
        if not p.is_file():
            return None, f"（NLP_WEEK7_HF_TOKEN_FILE 指向的文件不存在: {path}）"
        for line in p.read_text(encoding="utf-8").splitlines():
            s = line.split("#", 1)[0].strip()
            if s:
                return s, f"文件 {p}"
        return None, f"（NLP_WEEK7_HF_TOKEN_FILE 文件无有效行: {p}）"

    return None, "（未配置，将匿名访问 Hub）"


def apply_hf_token_before_hub_import() -> tuple[str | None, str]:
    """把令牌同步到进程环境，便于 huggingface_hub 在 import 后仍使用同一令牌。"""
    token, src = resolve_hf_token()
    if token:
        os.environ["HF_TOKEN"] = token
    return token, src


def read_sentences(path: str) -> list[str]:
    lines = []
    for raw in Path(path).read_text(encoding="utf-8").splitlines():
        s = raw.strip()
        if s:
            lines.append(s)
    return lines


def map_msra_tag(tag: str) -> str:
    t = (tag or "").upper()
    if t in ("NR", "PER", "PERSON"):
        return "PERSON"
    if t in ("NS", "LOC", "LOCATION", "GPE"):
        return "LOCATION"
    if t in ("NT", "ORG", "ORGANIZATION"):
        return "ORGANIZATION"
    if t in ("T", "TIME"):
        return "TIME"
    return tag or "MISC"


def map_clue_group(group: str) -> str:
    g = (group or "").lower()
    if g == "name":
        return "PERSON"
    if g in ("address",):
        return "LOCATION"
    if g in ("organization", "company", "government"):
        return "ORGANIZATION"
    if g in ("time",):
        return "TIME"
    return group or "MISC"


def _flatten_hanlp_ner_item(item, out: list[tuple[str, str, int | None, int | None]]) -> None:
    if item is None:
        return
    if isinstance(item, (list, tuple)):
        if len(item) >= 2 and isinstance(item[0], str) and isinstance(item[1], str):
            ent, tag = item[0], item[1]
            s = int(item[2]) if len(item) > 2 and item[2] is not None else None
            e = int(item[3]) if len(item) > 3 and item[3] is not None else None
            out.append((ent, tag, s, e))
            return
        for sub in item:
            _flatten_hanlp_ner_item(sub, out)
        return
    if isinstance(item, dict):
        for v in item.values():
            _flatten_hanlp_ner_item(v, out)


def normalize_hanlp_output(raw, n_sentences: int) -> list[list[tuple[str, str, int | None, int | None]]]:
    if raw is None:
        return [[] for _ in range(n_sentences)]
    per: list[list[tuple[str, str, int | None, int | None]]] = []

    def is_span_list(obj) -> bool:
        if not isinstance(obj, list) or not obj:
            return False
        first = obj[0]
        return (
            isinstance(first, (list, tuple))
            and len(first) >= 2
            and isinstance(first[0], str)
            and isinstance(first[1], str)
        )

    if n_sentences == 1:
        if is_span_list(raw):
            spans: list[tuple[str, str, int | None, int | None]] = []
            _flatten_hanlp_ner_item(raw, spans)
            return [spans]
        if isinstance(raw, list) and raw and isinstance(raw[0], list):
            for sent in raw:
                spans = []
                _flatten_hanlp_ner_item(sent, spans)
                per.append(spans)
            if len(per) == 1:
                return per
            if len(per) == 0:
                return [[]]
        spans = []
        _flatten_hanlp_ner_item(raw, spans)
        return [spans]

    if isinstance(raw, list):
        for sent in raw:
            spans = []
            _flatten_hanlp_ner_item(sent, spans)
            per.append(spans)
        if per:
            if len(per) > n_sentences:
                return per[:n_sentences]
            if len(per) < n_sentences:
                return per + [[] for _ in range(n_sentences - len(per))]
            return per

    spans = []
    _flatten_hanlp_ner_item(raw, spans)
    if n_sentences <= 1:
        return [spans]
    return [spans] + [[] for _ in range(n_sentences - 1)]


def try_build_hanlp_ner():
    import hanlp

    name = "MSRA_NER_BERT_BASE_ZH"
    if not hasattr(hanlp.pretrained.ner, name):
        for cand in ("MSRA_NER_ALBERT_BASE_ZH", "MSRA_NER_ELECTRA_SMALL_ZH"):
            if hasattr(hanlp.pretrained.ner, cand):
                name = cand
                break
    path = getattr(hanlp.pretrained.ner, name)
    return hanlp.load(path), f"hanlp:{name}"


def try_build_hf_ner():
    print(
        "\n[加载] 正在初始化 Transformers NER（首次会从 Hub 下载权重，体积较大，终端可能数分钟无新输出，属正常现象）。",
        flush=True,
    )
    hf_token, hf_src = apply_hf_token_before_hub_import()
    use_cli_token = _env_truthy("NLP_WEEK7_USE_HF_CLI_TOKEN")
    if hf_token:
        print(f"[加载] Hub 鉴权: 已提供访问令牌（来源: {hf_src}），长度 {len(hf_token)}。", flush=True)
    elif use_cli_token:
        print("[加载] Hub 鉴权: NLP_WEEK7_USE_HF_CLI_TOKEN=1，将使用 huggingface-cli 已登录缓存（token=True）。", flush=True)
    else:
        print(f"[加载] Hub 鉴权: {hf_src}", flush=True)

    print(
        "[加载] HF_HUB_DISABLE_XET=%s  HF_ENDPOINT=%s"
        % (
            os.environ.get("HF_HUB_DISABLE_XET", ""),
            os.environ.get("HF_ENDPOINT", "") or "（未设置）",
        ),
        flush=True,
    )
    from transformers import pipeline

    device = -1
    torch_ver = ""
    try:
        import torch

        torch_ver = getattr(torch, "__version__", "")
        device = 0 if torch.cuda.is_available() else -1
    except Exception:
        device = -1

    print("[加载] 开始构建 pipeline（下载结束后会打印推理结果）...", flush=True)
    pipe_kw: dict = {
        "model": HF_NER_MODEL,
        "tokenizer": HF_NER_MODEL,
        "aggregation_strategy": "simple",
        "device": device,
        "trust_remote_code": True,
    }
    if hf_token:
        pipe_kw["token"] = hf_token
    elif use_cli_token:
        pipe_kw["token"] = True

    clf = pipeline("ner", **pipe_kw)
    dev_s = "cuda" if device == 0 else "cpu"
    auth = "token" if hf_token else ("cli" if use_cli_token else "anon")
    meta = f"transformers+pytorch:{HF_NER_MODEL}  device={dev_s}  hub_auth={auth}"
    if torch_ver:
        meta += f"  torch={torch_ver}"
    return clf, meta


def run_hanlp_on_sentences(ner, sentences: list[str]) -> list[list[tuple[str, str, int | None, int | None]]]:
    if len(sentences) == 1:
        raw = ner(sentences[0])
        return normalize_hanlp_output(raw, 1)
    raw = ner(sentences)
    return normalize_hanlp_output(raw, len(sentences))


def run_hf_on_sentences(ner, sentences: list[str]) -> list[list[tuple[str, str, int | None, int | None]]]:
    out: list[list[tuple[str, str, int | None, int | None]]] = []
    for s in sentences:
        rows = ner(s)
        spans: list[tuple[str, str, int | None, int | None]] = []
        for ent in rows or []:
            word = ent.get("word", "")
            grp = ent.get("entity_group", ent.get("label", ""))
            spans.append((word, str(grp), int(ent.get("start", -1)), int(ent.get("end", -1))))
        out.append(spans)
    return out


def print_table(title: str, backend: str, sentences: list[str], per_sent_spans: list[list[tuple[str, str, int | None, int | None]]], mapper) -> None:
    print(f"\n--- {title} ---")
    print(f"后端: {backend}")
    print("序号 | 原句 | 实体 | 原始标签 | 归一类型 | 字符起止(若有)")
    print("-" * 72)
    for i, (sent, spans) in enumerate(zip(sentences, per_sent_spans), 1):
        if not spans:
            print(f"{i:>2} | {sent} | （无实体） |  |  |  ")
            continue
        for j, (text, raw_tag, s, e) in enumerate(spans):
            norm = mapper(raw_tag)
            se = "" if s is None or e is None or s < 0 else f"{s}-{e}"
            prefix = f"{i:>2} | {sent}" if j == 0 else f"{'':>2} | {'':<}"
            print(f"{prefix} | {text} | {raw_tag} | {norm} | {se}")


def extract_times_regex(sentence: str) -> list[str]:
    return re.findall(r"\d{4}\s*年\s*\d{1,2}\s*月\s*\d{1,2}\s*日", sentence)


def _env_truthy(name: str) -> bool:
    v = os.environ.get(name, "").strip().lower()
    return v in ("1", "true", "yes", "on")


def main():
    print(f"数据文件: {DATA_PATH}")
    print(f"NER 模型: {HF_NER_MODEL}")
    print("默认优先 PyTorch 路线（Transformers）。若需先 HanLP，请设置 NLP_WEEK7_TRY_HANLP_FIRST=1。")
    print("若首次下载模型较慢，请配置代理或 HF_ENDPOINT 等镜像环境变量。")
    print("Hub 令牌: 可设 HF_TOKEN、HUGGING_FACE_HUB_TOKEN，或 NLP_WEEK7_HF_TOKEN_FILE 指向单行密钥文件。")
    print(
        "Hub 提示: 默认 HF_HUB_DISABLE_XET=1 以避免 XET 下载路径卡住；若你已在环境显式设为 0，将按你的设置使用。"
    )

    sentences = read_sentences(DATA_PATH)
    if not sentences:
        print("数据文件为空，请检查路径与内容。")
        return

    print("\n--- 实验十三 命名实体识别：逐句结果（便于报告截图） ---")

    hanlp_first = _env_truthy("NLP_WEEK7_TRY_HANLP_FIRST")
    order: list[tuple[str, object, object, object, str]] = []
    if hanlp_first:
        order = [
            ("hanlp", try_build_hanlp_ner, run_hanlp_on_sentences, map_msra_tag, "HanLP（任务书可选工具）"),
            ("hf", try_build_hf_ner, run_hf_on_sentences, map_clue_group, "Transformers 与 PyTorch（默认推荐）"),
        ]
    else:
        order = [
            ("hf", try_build_hf_ner, run_hf_on_sentences, map_clue_group, "Transformers 与 PyTorch（默认推荐）"),
            ("hanlp", try_build_hanlp_ner, run_hanlp_on_sentences, map_msra_tag, "HanLP（可选）"),
        ]

    last_err: Exception | None = None
    for key, build, run, mapper, title in order:
        try:
            ner, backend = build()
            spans = run(ner, sentences)
            print_table(title, backend, sentences, spans, mapper)
            last_err = None
            break
        except Exception as exc:
            last_err = exc
            print(f"\n{title.split('（')[0]} 未启用或失败，尝试下一后端。")
            print(f"  异常类型: {type(exc).__name__}  信息: {exc}")
            low = str(exc).lower()
            if key == "hanlp" and (
                "tensorflow" in low or "hanlp[full]" in low or "required by this model" in low
            ):
                print('  提示: HanLP 该模型需 pip install "hanlp[full]" -U，或改用默认 PyTorch 路线（勿设 NLP_WEEK7_TRY_HANLP_FIRST）。')
            if key == "hf" and ("28" in str(exc) or "no space" in low):
                print("  提示: 若为磁盘空间不足，请清理 C 盘或设置 TEMP、TMP、PIP_CACHE_DIR 到大空间盘后再下载模型。")
    else:
        if last_err is not None:
            print("\n所有后端均失败。PyTorch 路线请确认: pip install torch transformers huggingface_hub，并保证可联网或代理下载模型。")
        return

    print("\n--- 时间表达式（正则辅助，可与模型 TIME 类型对照） ---")
    for i, s in enumerate(sentences, 1):
        ts = extract_times_regex(s)
        print(f"  [{i}] {s}")
        print(f"      正则抽取到的日期片段: {ts if ts else '（无）'}")



if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print(
            "\n[中断] 已取消模型下载或加载。若曾长时间无输出，多为网络或 Hub 存储后端导致，"
            "请保持代理开启，或设置 HF_ENDPOINT 镜像，并确认 HF_HUB_DISABLE_XET=1 后重试。",
            flush=True,
        )
        raise SystemExit(130) from None
