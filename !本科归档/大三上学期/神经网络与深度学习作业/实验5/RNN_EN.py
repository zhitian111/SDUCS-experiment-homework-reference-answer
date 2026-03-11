import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, Dataset
import pandas as pd
import numpy as np
from collections import Counter
from torch.nn.utils.rnn import pad_sequence

# 超参数
VOCAB_SIZE = 20000
EMBED_DIM = 100
HIDDEN_DIM = 128
OUTPUT_DIM = 4
BATCH_SIZE = 64
NUM_EPOCHS = 5

# 设备
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model_path = "lstm_agnews.pt"


import os, torch

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
# 分词器（简单空格分词）
tokenizer = lambda x: x.lower().split()

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



@torch.no_grad()
def evaluate(model, loader):
    model.eval()
    correct, total = 0, 0
    for labels, seqs in loader:
        labels, seqs = labels.to(device), seqs.to(device)
        preds = model(seqs).argmax(1)
        correct += (preds == labels).sum().item()
        total   += labels.size(0)
    return correct / total

ag_news_label = {0: "World", 1: "Sports", 2: "Business", 3: "Sci/Tech"}

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
    ex_text_str = "MEMPHIS,Tenn.Four days ago, Jon Rahm was enduring the season's worst weather conditions on Sunday at The \
                Open on his way to a closing 75 at Royal Portrush, which \
                considering the wind and the rain was a respectable showing. \
                Thursdays first round at the WGC - FedEx St.Jude Invitational was another story.With temperatures in the mid - 80 s and hardly any \
                wind, the Spaniard was 13 strokes better in a flawless round. \
                Thanks to his best putting performance on the PGA Tour, Rahm \
                was finished with an8 - under 62 for a three-stroke lead, which \
                was even more impressive considering hed never played the \
                front nine at TPc Southwind."
    # model = model.to("cpu")
    print("This is a %s news" % ag_news_label[predict(ex_text_str)])
    save_model(model)
# ========= 加载后单独评测 =========
def evaluate_test(model, vocab, test_path="data/test.csv"):
    from torch.utils.data import DataLoader
    test_ds = AGNewsDataset(test_path, vocab)
    test_loader = DataLoader(test_ds, batch_size=BATCH_SIZE,
                             shuffle=False, collate_fn=collate_batch)
    acc = evaluate(model, test_loader)          # 复用前面写好的 evaluate
    print(f"[INFO] Evaluating on test set ...\nTest Accuracy: {acc:.4f}")
if __name__ == "__main__" and os.path.exists(model_path):
    model, vocab = load_model()
    ex_text_str = "MEMPHIS,Tenn.Four days ago, Jon Rahm was enduring the season's worst weather conditions on Sunday at The \
                Open on his way to a closing 75 at Royal Portrush, which \
                considering the wind and the rain was a respectable showing. \
                Thursdays first round at the WGC - FedEx St.Jude Invitational was another story.With temperatures in the mid - 80 s and hardly any \
                wind, the Spaniard was 13 strokes better in a flawless round. \
                Thanks to his best putting performance on the PGA Tour, Rahm \
                was finished with an8 - under 62 for a three-stroke lead, which \
                was even more impressive considering hed never played the \
                front nine at TPc Southwind."
    # model = model.to("cpu")
    print("This is a %s news" % ag_news_label[predict(ex_text_str)])
    evaluate_test(model, vocab)