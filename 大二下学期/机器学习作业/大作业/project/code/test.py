import csv
import torch
import torch.nn as nn
import torch.utils.data as data
import tqdm as tq
import math
import zipfile
import os

# 设备选择
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"使用设备: {device}")

# 位置编码类
class PositionalEncoding(nn.Module):
    def __init__(self, d_model, max_len=80):
        super(PositionalEncoding, self).__init__()
        pe = torch.zeros(max_len, d_model)
        position = torch.arange(0, max_len, dtype=torch.float).unsqueeze(1)
        div_term = torch.exp(torch.arange(0, d_model, 2).float() * (-math.log(10000.0) / d_model))
        pe[:, 0::2] = torch.sin(position * div_term)
        pe[:, 1::2] = torch.cos(position * div_term)
        pe = pe.unsqueeze(0)
        self.register_buffer('pe', pe)

    def forward(self, x):
        x = x + self.pe[:, :x.size(1), :]
        return x

# 语义相似性模型
class SemanticSimilarityModel(nn.Module):
    def __init__(self, input_dim=1, d_model=512, nhead=8, num_encoder_layers=6, dim_feedforward=2048, dropout=0.1):
        super(SemanticSimilarityModel, self).__init__()
        self.embedding = nn.Linear(input_dim, d_model)
        self.pos_encoder = PositionalEncoding(d_model)
        encoder_layer = nn.TransformerEncoderLayer(
            d_model=d_model,
            nhead=nhead,
            dim_feedforward=dim_feedforward,
            dropout=dropout,
            batch_first=True
        )
        self.transformer_encoder = nn.TransformerEncoder(encoder_layer, num_layers=num_encoder_layers)
        self.d_model = d_model
        self.fc = nn.Linear(1, 1)
        self.dropout = nn.Dropout(dropout)

    def forward(self, seq1, seq2):
        seq1 = seq1.unsqueeze(-1)
        seq2 = seq2.unsqueeze(-1)
        emb1 = self.embedding(seq1) * math.sqrt(self.d_model)
        emb2 = self.embedding(seq2) * math.sqrt(self.d_model)
        emb1 = self.pos_encoder(emb1)
        emb2 = self.pos_encoder(emb2)
        mask1 = (seq1.squeeze(-1) == 0)
        mask2 = (seq2.squeeze(-1) == 0)
        enc1 = self.transformer_encoder(emb1, src_key_padding_mask=mask1)
        enc2 = self.transformer_encoder(emb2, src_key_padding_mask=mask2)
        rep1 = torch.mean(enc1, dim=1)
        rep2 = torch.mean(enc2, dim=1)
        rep1_norm = torch.nn.functional.normalize(rep1, p=2, dim=1)
        rep2_norm = torch.nn.functional.normalize(rep2, p=2, dim=1)
        cos_sim = torch.sum(rep1_norm * rep2_norm, dim=1).unsqueeze(-1)
        cos_sim = self.dropout(cos_sim)
        logits = self.fc(cos_sim)
        return logits.squeeze(-1)

# 数据切片类
class DataSlice:
    def __init__(self, seq1, seq2, mean_val, std_val, padding=80):
        self.seq1 = [(float(i) - mean_val) / std_val if float(i) != 0 else 0 for i in seq1]
        self.seq1.extend([0] * (padding - len(self.seq1)))
        self.seq2 = [(float(i) - mean_val) / std_val if float(i) != 0 else 0 for i in seq2]
        self.seq2.extend([0] * (padding - len(self.seq2)))
    
    @classmethod
    def from_csv_row(cls, row, mean_val, std_val, padding=80):
        return cls(row[0].split(), row[1].split(), mean_val, std_val, padding)

# 数据集类
class InferenceDataset(data.Dataset):
    def __init__(self, data_slices):
        self.data_slices = data_slices
    
    def __len__(self):
        return len(self.data_slices)
    
    def __getitem__(self, index):
        item = self.data_slices[index]
        return (
            torch.tensor(item.seq1, dtype=torch.float32),
            torch.tensor(item.seq2, dtype=torch.float32)
        )

# 加载数据
def load_inference_data(file_path, mean_val, std_val, padding=80):
    with open(file_path, 'r', encoding='utf-8') as f:
        reader = csv.reader(f, delimiter='\t')
        data_slices = []
        for row in tq.tqdm(reader, desc="加载推理数据"):
            data_slices.append(DataSlice.from_csv_row(row, mean_val, std_val, padding))
    return InferenceDataset(data_slices)

# 预测函数
def predict(model, dataset, batch_size=32, device='cuda'):
    data_loader = data.DataLoader(dataset, batch_size=batch_size, shuffle=False)
    model = model.to(device)
    model.eval()
    probabilities = []
    with torch.no_grad():
        for seq1, seq2 in tq.tqdm(data_loader, desc="生成预测"):
            seq1, seq2 = seq1.to(device), seq2.to(device)
            outputs = model(seq1, seq2)
            probs = torch.sigmoid(outputs)  # 转换为概率 [0, 1]
            probabilities.extend(probs.cpu().numpy())
    return probabilities

if __name__ == "__main__":
    # 超参数
    model_path = 'best_model.pt'
    data_path = '../tcdata/oppo_breeno_round1_data/testB.tsv'  # 替换为你的新 CSV 文件路径
    mean_val = 813.9287261037828  # 训练时的均值
    std_val = 1940.1439092779256  # 训练时的标准差
    padding = 80  # 与训练时的填充长度一致
    batch_size = 32
    output_file = 'result.txt'
    zip_file = 'result.zip'

    # 初始化模型
    model = SemanticSimilarityModel(input_dim=1, d_model=512, nhead=8, num_encoder_layers=6, dim_feedforward=2048, dropout=0.1)
    model.load_state_dict(torch.load(model_path, map_location=device))
    print("模型加载完成")

    # 加载数据
    dataset = load_inference_data(data_path, mean_val, std_val, padding)
    print("数据加载完成")

    # 进行预测
    probabilities = predict(model, dataset, batch_size, device)
    print("预测完成")

    # 保存预测结果到文本文件
    with open(output_file, 'w', encoding='utf-8') as f:
        for prob in probabilities:
            f.write(f"{prob:.6f}\n")  # 保留 6 位小数
    print(f"预测结果已保存至 {output_file}")

    # 压缩结果文件为 zip
    with zipfile.ZipFile(zip_file, 'w', zipfile.ZIP_DEFLATED) as zf:
        zf.write(output_file)
    print(f"结果文件已压缩为 {zip_file}")

    # 删除临时文本文件
    os.remove(output_file)
    print(f"临时文件 {output_file} 已删除")