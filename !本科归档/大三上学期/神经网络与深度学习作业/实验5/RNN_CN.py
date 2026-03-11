import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, Dataset
import numpy as np
import pandas as pd, jieba, torch, random
from collections import Counter
from torch.nn.utils.rnn import pad_sequence
import os
N_SAMPLE = 20_000
SEED     = 42
random.seed(SEED)

df = pd.read_csv('./data/toutiao_news_dataset.txt', sep='_!_', header=None,
                 names=['id','label_id','text'], usecols=[0,1,2],
                 dtype=str, encoding='utf-8')

df = df.sample(n=N_SAMPLE, random_state=SEED).reset_index(drop=True)
label2id = {l:i for i,l in enumerate(df['label_id'].unique())}
id2label = {i:l for l,i in label2id.items()}   # 可选：打印用
# 100 民生 故事 news_story
# 101 文化 文化 news_culture
# 102 娱乐 娱乐 news_entertainment
# 103 体育 体育 news_sports
# 104 财经 财经 news_finance
# 106 房产 房产 news_house
# 107 汽车 汽车 news_car
# 108 教育 教育 news_edu
# 109 科技 科技 news_tech
# 110 军事 军事 news_military
# 112 旅游 旅游 news_travel
# 113 国际 国际 news_world
# 114 证券 股票 stock
# 115 农业 三农 news_agriculture
# 116 电竞 游戏 news_game
label_name = {'100' : "民生", '101' : "文化", '102' : "娱乐", '103' : "体育", '104' : "财经", '106' : "房产", '107' : "汽车", '108' : "教育", '109' : "科技", '110' : "军事", '112' : "旅游", '114' : "证券", '115' : "农业", '116' : "电竞"}

tokenizer = lambda x: list(jieba.cut(x, cut_all=False))

# 超参数
VOCAB_SIZE = 20000
EMBED_DIM = 100
HIDDEN_DIM = 128
OUTPUT_DIM = 4
BATCH_SIZE = 64
NUM_EPOCHS = 5

# 设备
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model_path = "lstm_agnews_cn.pt"




# ---------- 保存 ----------
def save_model(model, filepath=model_path):
    torch.save({
        'model_state_dict': model.state_dict(),
        'vocab': vocab,                # 训练时的全局变量
        'model_hparams': {
            'vocab_size': len(vocab),
            'embed_dim' : EMBED_DIM,
            'hidden_dim': HIDDEN_DIM,
            'output_dim': OUTPUT_DIM
        }
    }, filepath)
    print(f"[INFO] LSTM model saved -> {filepath}")

# ---------- 加载 ----------
def load_model(filepath=model_path, device=device):
    if not os.path.isfile(filepath):
        raise FileNotFoundError(filepath)

    ckpt = torch.load(filepath, map_location=device)
    hp   = ckpt['model_hparams']

    # 重建 LSTM 模型
    model = LSTMClassifier(
        vocab_size=hp['vocab_size'],
        embed_dim=hp['embed_dim'],
        hidden_dim=hp['hidden_dim'],
        output_dim=hp['output_dim']
    ).to(device)

    model.load_state_dict(ckpt['model_state_dict'])
    model.eval()
    print(f"[INFO] LSTM model loaded <- {filepath}")
    return model, ckpt['vocab']

# 构建词汇表
def build_vocab(filepath, max_vocab=VOCAB_SIZE):
    counter = Counter()
    df = pd.read_csv(filepath, names=["label", "title", "description"])
    for text in df["title"] + " " + df["description"]:
        counter.update(tokenizer(str(text)))
    vocab = {"<pad>": 0, "<unk>": 1}
    for word, _ in counter.most_common(max_vocab - 2):
        vocab[word] = len(vocab)
    return vocab

# 数据集
class AGNewsDataset(Dataset):
    def __init__(self, filepath, vocab):
        self.vocab = vocab
        self.data = []
        df = pd.read_csv(filepath, names=["label", "title", "description"])
        for label, title, desc in zip(df["label"], df["title"], df["description"]):
            tokens = tokenizer(str(title) + " " + str(desc))
            ids = [self.vocab.get(w, self.vocab["<unk>"]) for w in tokens]
            self.data.append((int(label) - 1, torch.tensor(ids, dtype=torch.long)))

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        label, text = self.data[idx]
        return label, text

# 填充批次
def collate_batch(batch):
    labels, texts = zip(*batch)
    labels = torch.tensor(labels, dtype=torch.long)
    texts = pad_sequence(texts, batch_first=True, padding_value=0)
    return labels, texts

# 模型：LSTM
class LSTMClassifier(nn.Module):
    def __init__(self, vocab_size, embed_dim, hidden_dim, output_dim):
        super().__init__()
        self.embedding = nn.Embedding(vocab_size, embed_dim, padding_idx=0)
        self.lstm = nn.LSTM(embed_dim, hidden_dim, batch_first=True)
        self.fc = nn.Linear(hidden_dim, output_dim)

    def forward(self, x):
        embedded = self.embedding(x)
        _, (hidden, _) = self.lstm(embedded)
        return self.fc(hidden.squeeze(0))

def predict(text: str):
    """返回类别 id"""
    model.eval()
    tokens = [vocab.get(w, vocab["<unk>"]) for w in tokenizer(text)]
    seq = torch.tensor(tokens, dtype=torch.long).unsqueeze(0)  # [1, T]
    with torch.no_grad():
        logits = model(seq.to(device))      # [1, 4]
    return logits.argmax(1).item()

# 主流程
if __name__ == "__main__" and not os.path.exists(model_path):
    vocab = build_vocab("data/train.csv")
    train_ds = AGNewsDataset("data/train.csv", vocab)
    test_ds = AGNewsDataset("data/test.csv", vocab)

    train_loader = DataLoader(train_ds, batch_size=BATCH_SIZE, shuffle=True, collate_fn=collate_batch)
    test_loader = DataLoader(test_ds, batch_size=BATCH_SIZE, shuffle=False, collate_fn=collate_batch)

    model = LSTMClassifier(len(vocab), EMBED_DIM, HIDDEN_DIM, OUTPUT_DIM).to(device)
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.Adam(model.parameters(), lr=1e-3)

    # 训练
    for epoch in range(NUM_EPOCHS):
        model.train()
        total_loss = 0
        for labels, texts in train_loader:
            labels, texts = labels.to(device), texts.to(device)
            optimizer.zero_grad()
            outputs = model(texts)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()
            total_loss += loss.item()
        print(f"Epoch {epoch+1}, Loss: {total_loss / len(train_loader):.4f}")

    # 测试
    model.eval()
    correct, total = 0, 0
    with torch.no_grad():
        for labels, texts in test_loader:
            labels, texts = labels.to(device), texts.to(device)
            outputs = model(texts)
            preds = outputs.argmax(1)
            correct += (preds == labels).sum().item()
            total += labels.size(0)
    print(f"Test Accuracy: {correct / total:.4f}")
    text = "中国女足晋级世界杯决赛！"
    print("这是 %s 新闻" % label_name[id2label[predict(text)]])
    save_model(model)

if __name__ == "__main__" and os.path.exists(model_path):
    model, vocab = load_model()
    text = "中国女足晋级世界杯决赛！"
    print("这是 %s 新闻" % label_name[id2label[predict(text)]])