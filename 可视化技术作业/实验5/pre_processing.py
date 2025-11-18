import csv
import json

# ================================
# 参数
# ================================
TARGET_FILE = "./git_web_ml/musae_git_target.csv"
FEATURES_FILE = "./git_web_ml/musae_git_features.json"
EDGES_FILE = "./git_web_ml/musae_git_edges.csv"

OUTPUT_FILE = "graph_data_small.js"

MAX_NODES = 1000  # ⭐⭐ 你想保留多少节点，改这里 ⭐⭐
# ================================


# 读取特征
print("读取特征文件...")
with open(FEATURES_FILE, "r", encoding="utf-8") as f:
    features = json.load(f)


# 读取节点
print("读取 musae_git_target.csv...")
nodes = []
with open(TARGET_FILE, "r", encoding="utf-8") as f:
    reader = csv.DictReader(f)
    for row in reader:
        node_id = int(row["id"])
        name = row["name"]
        feature = features.get(str(node_id), [])
        nodes.append({
            "id": node_id,
            "name": name,
            "feature": feature
        })


# 根据数量限制取前 N 个节点
print(f"限制节点数量为 {MAX_NODES} 个...")
nodes_small = nodes[:MAX_NODES]
allowed_ids = set(n["id"] for n in nodes_small)


# 过滤边（只保留参与的节点）
print("过滤边...")
edges_small = []
with open(EDGES_FILE, "r", encoding="utf-8") as f:
    reader = csv.DictReader(f)
    for row in reader:
        s = int(row["id_1"])
        t = int(row["id_2"])
        if s in allowed_ids and t in allowed_ids:
            edges_small.append({"source": s, "target": t})


# 导出 JS 文件
print("正在生成 graph_data_small.js ...")
with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
    f.write("const nodes = ")
    f.write(json.dumps(nodes_small, ensure_ascii=False, indent=4))
    f.write(";\n\n")
    f.write("const edges = ")
    f.write(json.dumps(edges_small, ensure_ascii=False, indent=4))
    f.write(";")


print("完成！")
print(f"输出文件：{OUTPUT_FILE}")
print(f"节点数量：{len(nodes_small)}")
print(f"边数量：{len(edges_small)}")
