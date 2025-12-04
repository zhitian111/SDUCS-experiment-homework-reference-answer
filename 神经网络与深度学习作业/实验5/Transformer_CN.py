import torch, math
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, Dataset
import pandas as pd
from collections import Counter
from torch.nn.utils.rnn import pad_sequence

# ========= 超参数 =========
VOCAB_SIZE   = 20_000
D_MODEL      = 256      # d_model
N_HEAD       = 8
NUM_LAYERS   = 4
DIM_FF       = 512
MAX_LEN      = 256
BATCH_SIZE   = 64
NUM_EPOCHS   = 5
NUM_CLASSES  = 4
DEVICE       = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model_path   = "transformer_agnews_cn.pt"

import os
import torch
N_SAMPLE = 20_000
SEED = 42

import jieba
df = pd.read_csv('./data/toutiao_news_dataset.txt', sep='_!_', header=None,
                 names=['id','label_id','text'], usecols=[0,1,2],
                 dtype=str, encoding='utf-8')

df = df.sample(n=N_SAMPLE, random_state=SEED).reset_index(drop=True)
label2id = {l:i for i,l in enumerate(df['label_id'].unique())}
id2label = {i:l for l,i in label2id.items()}   # 可选：打印用
label_name = {'100' : "民生", '101' : "文化", '102' : "娱乐", '103' : "体育", '104' : "财经", '106' : "房产", '107' : "汽车", '108' : "教育", '109' : "科技", '110' : "军事", '112' : "旅游", '114' : "证券", '115' : "农业", '116' : "电竞"}

tokenizer = lambda x: list(jieba.cut(x, cut_all=False))


# ---------- 保存 ----------
def save_model(model, filepath=model_path):
    """
    保存模型权重 + 超参 + vocab，一站式打包
    """
    torch.save({
        'model_state_dict': model.state_dict(),
        'vocab': vocab,                    # 前面全局变量
        'model_hparams': {
            'vocab_size': len(vocab),
            'd_model'   : D_MODEL,
            'nhead'     : N_HEAD,
            'num_layers': NUM_LAYERS,
            'dim_ff'    : DIM_FF,
            'num_classes': NUM_CLASSES
        }
    }, filepath)
    print(f"[INFO] Model saved -> {filepath}")

# ---------- 加载 ----------
def load_model(filepath=model_path, device=DEVICE):
    """
    从磁盘恢复模型（含权重），返回已.eval()的模型
    """
    if not os.path.isfile(filepath):
        raise FileNotFoundError(filepath)

    checkpoint = torch.load(filepath, map_location=device)

    # 重建模型骨架
    hp = checkpoint['model_hparams']
    model = TransformerCls(
        vocab_size=hp['vocab_size'],
        d_model=hp['d_model'],
        nhead=hp['nhead'],
        num_layers=hp['num_layers'],
        dim_ff=hp['dim_ff'],
        num_classes=hp['num_classes']
    ).to(device)

    model.load_state_dict(checkpoint['model_state_dict'])
    model.eval()                      # 推断模式
    print(f"[INFO] Model loaded <- {filepath}")
    return model, checkpoint['vocab']  # 同时返回 vocab，方便 predict



def build_vocab(path):
    counter = Counter()
    df = pd.read_csv(path, names=["label", "title", "description"])
    for sent in df["title"] + " " + df["description"]:
        counter.update(tokenizer(str(sent)))
    vocab = {"<pad>": 0, "<unk>": 1}
    for w, _ in counter.most_common(VOCAB_SIZE - 2):
        vocab[w] = len(vocab)
    return vocab

class AGNewsDataset(Dataset):
    def __init__(self, path, vocab):
        self.vocab, self.data = vocab, []
        df = pd.read_csv(path, names=["label", "title", "description"])
        for label, title, desc in zip(df["label"], df["title"], df["description"]):
            ids = [self.vocab.get(w, self.vocab["<unk>"]) for w in tokenizer(str(title)+" "+str(desc))][:MAX_LEN]
            self.data.append((int(label) - 1, torch.tensor(ids, dtype=torch.long)))

    def __len__(self): return len(self.data)
    def __getitem__(self, idx): return self.data[idx]

def collate(batch):
    labels, seqs = zip(*batch)
    labels = torch.tensor(labels, dtype=torch.long)
    seqs   = pad_sequence(seqs, batch_first=True, padding_value=0)[:, :MAX_LEN]
    return labels, seqs

class TransformerCls(nn.Module):
    def __init__(self, vocab_size, d_model, nhead, num_layers, dim_ff, num_classes):
        super().__init__()
        self.embed = nn.Embedding(vocab_size, d_model, padding_idx=0)
        # 位置编码：直接利用 nn.Parameter 训练式位置向量（可换 sin/cos）
        self.pos   = nn.Parameter(torch.empty(1, MAX_LEN, d_model))
        nn.init.uniform_(self.pos, -0.1, 0.1)

        # TransformerEncoderLayer + Encoder
        encoder_layer = nn.TransformerEncoderLayer(
            d_model=d_model,
            nhead=nhead,
            dim_feedforward=dim_ff,
            dropout=0.1,
            activation='relu',
            batch_first=True          # 输入 [B, T, D]
        )
        self.transformer = nn.TransformerEncoder(encoder_layer, num_layers=num_layers)

        self.fc = nn.Linear(d_model, num_classes)

    def forward(self, x):
        mask = (x == 0)                                    # pad mask
        x = self.embed(x) + self.pos[:, :x.size(1), :]     # 加位置
        out = self.transformer(x, src_key_padding_mask=mask)  # [B, T, D]
        # 全局平均池化（pad 位置已 masked）
        out = out.masked_fill(mask.unsqueeze(-1), 0.).sum(dim=1)
        out = out / (~mask).sum(dim=1, keepdim=True).clamp(min=1)
        return self.fc(out)                                # [B, num_classes]

def train_epoch(model, loader, criterion, optimizer):
    model.train()
    total = 0.
    for labels, seqs in loader:
        labels, seqs = labels.to(DEVICE), seqs.to(DEVICE)
        optimizer.zero_grad()
        loss = criterion(model(seqs), labels)
        loss.backward()
        optimizer.step()
        total += loss.item()
    return total / len(loader)

@torch.no_grad()
def evaluate(model, loader):
    model.eval()
    correct, total = 0, 0
    for labels, seqs in loader:
        labels, seqs = labels.to(DEVICE), seqs.to(DEVICE)
        preds = model(seqs).argmax(1)
        correct += (preds == labels).sum().item()
        total   += labels.size(0)
    return correct / total
def predict(text: str):
    """返回类别 id"""
    model.eval()
    tokens = [vocab.get(w, vocab["<unk>"]) for w in tokenizer(text)]
    seq = torch.tensor(tokens, dtype=torch.long).unsqueeze(0)  # [1, T]
    with torch.no_grad():
        logits = model(seq.to(DEVICE))      # [1, 4]
    return logits.argmax(1).item()
if __name__ == "__main__" and not os.path.exists(model_path):
    vocab = build_vocab("data/train.csv")
    train_loader = DataLoader(AGNewsDataset("data/train.csv", vocab),
                              batch_size=BATCH_SIZE, shuffle=True, collate_fn=collate)
    test_loader  = DataLoader(AGNewsDataset("data/test.csv", vocab),
                              batch_size=BATCH_SIZE, shuffle=False, collate_fn=collate)

    model = TransformerCls(len(vocab), D_MODEL, N_HEAD, NUM_LAYERS, DIM_FF, NUM_CLASSES).to(DEVICE)
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.Adam(model.parameters(), lr=1e-3)

    for epoch in range(1, NUM_EPOCHS + 1):
        tr_loss = train_epoch(model, train_loader, criterion, optimizer)
        acc     = evaluate(model, test_loader)
        print(f"Epoch {epoch}/{NUM_EPOCHS}  |  loss {tr_loss:.4f}  |  test acc {acc:.4f}")

    text = "中国女足晋级世界杯决赛！"
    print("这是 %s 新闻" % label_name[id2label[predict(text)]])
    save_model(model)

if __name__ == "__main__" and os.path.exists(model_path):
    model, vocab = load_model()
    text = "山东大学宋浩宇研制出了能够对中文新闻进行分类的模型！"
    print("这是 %s 新闻" % label_name[id2label[predict(text)]])