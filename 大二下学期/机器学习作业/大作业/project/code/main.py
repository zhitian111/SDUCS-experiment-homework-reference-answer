import csv
import time
import tqdm as tq
import torch
import torch.nn as nn
import torch.optim as optim
import torch.utils.data as data

# 时间戳记录
class TimeStamp:
    def __init__(self, event):
        self.current_time = time.localtime()
        self.event = event
    def show(self):
        print(time.strftime("[%Y-%m-%d %H:%M:%S]\t", self.current_time), self.event)

time_stamps = []
def show_time_stamps():
    print("时间戳记录如下:")
    for ts in time_stamps:
        if ts is TimeStamp:
            ts.show()
    print("总共用时:", time.mktime(time_stamps[-1].current_time) - time.mktime(time_stamps[0].current_time), "秒")

time_stamps.append(TimeStamp("程序开始").show())

# 设备选择
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
time_stamps.append(TimeStamp(f"设备选择完成: {device}").show())

# 数据路径和参数
data_path = "../tcdata/oppo_breeno_round1_data/"
train_data_path = data_path + "train.tsv"
test_data_path = data_path + "testB.tsv"
padding_length = 80

# 数据加载
def get_file_length(filename):
    with open(filename, 'r') as f:
        return len(f.readlines())

def load_all_data():
    train_file = open(train_data_path, 'r', encoding='utf-8')
    test_file = open(test_data_path, 'r', encoding='utf-8')
    train_reader = csv.reader(train_file, delimiter='\t')
    test_reader = csv.reader(test_file, delimiter='\t')
    
    # 计算均值和标准差
    all_values = []
    train_reader_temp = list(train_reader)
    for row in train_reader_temp:
        seq1 = [float(i) for i in row[0].split() if float(i) != 0]
        seq2 = [float(i) for i in row[1].split() if float(i) != 0]
        all_values.extend(seq1 + seq2)
    mean_val = sum(all_values) / len(all_values) if all_values else 0
    std_val = (sum((x - mean_val)**2 for x in all_values) / len(all_values))**0.5 if all_values else 1
    print(f"数据均值: {mean_val:.4f}, 标准差: {std_val:.4f}")

    # 加载数据
    train_data = [TrainDataSlice.from_csv_row(row, mean_val, std_val) for row in tq.tqdm(train_reader_temp, desc="加载训练数据")]
    test_data = [TestDataSlice.from_csv_row(row, mean_val, std_val) for row in tq.tqdm(test_reader, desc="加载测试数据")]
    
    train_size = int(0.8 * len(train_data))
    return TrainDataSet(train_data[:train_size]), TrainDataSet(train_data[train_size:]), TestDataSet(test_data)

class TrainDataSlice:
    def __init__(self, seq1, seq2, similarity, mean_val, std_val):
        self.seq1 = [(float(i) - mean_val) / std_val if float(i) != 0 else 0 for i in seq1]
        self.seq1.extend([0] * (padding_length - len(self.seq1)))
        self.seq2 = [(float(i) - mean_val) / std_val if float(i) != 0 else 0 for i in seq2]
        self.seq2.extend([0] * (padding_length - len(self.seq2)))
        self.similarity = float(similarity)
    @classmethod
    def from_csv_row(cls, row, mean_val, std_val):
        return cls(row[0].split(), row[1].split(), row[2], mean_val, std_val)

class TestDataSlice:
    def __init__(self, seq1, seq2, mean_val, std_val):
        self.seq1 = [(float(i) - mean_val) / std_val if float(i) != 0 else 0 for i in seq1]
        self.seq1.extend([0] * (padding_length - len(self.seq1)))
        self.seq2 = [(float(i) - mean_val) / std_val if float(i) != 0 else 0 for i in seq2]
        self.seq2.extend([0] * (padding_length - len(self.seq2)))
    @classmethod
    def from_csv_row(cls, row, mean_val, std_val):
        return cls(row[0].split(), row[1].split(), mean_val, std_val)

class TrainDataSet(data.Dataset):
    def __init__(self, data_slices):
        self.data_slices = data_slices
    def __len__(self):
        return len(self.data_slices)
    def __getitem__(self, index):
        item = self.data_slices[index]
        return (
            torch.tensor(item.seq1, dtype=torch.float32),
            torch.tensor(item.seq2, dtype=torch.float32),
            torch.tensor(item.similarity, dtype=torch.float32)
        )

class TestDataSet(data.Dataset):
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

# 模型定义
class SimilarityModel(nn.Module):
    def __init__(self, input_dim=1, hidden_dim=128, num_layers=1, dropout=0.2):
        super(SimilarityModel, self).__init__()
        self.embedding = nn.Linear(input_dim, hidden_dim)
        self.lstm = nn.LSTM(hidden_dim, hidden_dim, num_layers=num_layers, bidirectional=True, batch_first=True, dropout=dropout if num_layers > 1 else 0)
        self.fc = nn.Sequential(
            nn.Linear(hidden_dim * 2, 64),
            nn.ReLU(),
            nn.Dropout(dropout),
            nn.Linear(64, 1)
        )
        self.layer_norm = nn.LayerNorm(hidden_dim * 2)

    def forward(self, seq1, seq2):
        seq1 = self.embedding(seq1.unsqueeze(-1))  # [batch, seq_len, hidden_dim]
        seq2 = self.embedding(seq2.unsqueeze(-1))
        _, (hidden1, _) = self.lstm(seq1)
        _, (hidden2, _) = self.lstm(seq2)
        hidden1 = torch.cat((hidden1[-2], hidden1[-1]), dim=1)  # [batch, hidden_dim * 2]
        hidden2 = torch.cat((hidden2[-2], hidden2[-1]), dim=1)
        hidden1 = self.layer_norm(hidden1)
        hidden2 = self.layer_norm(hidden2)
        combined = hidden1 * hidden2  # Element-wise multiplication
        logits = self.fc(combined)
        return logits.squeeze(-1)

# 训练函数
def train_model(model, train_dataset, val_dataset, num_epochs=10, batch_size=64, lr=1e-3):
    train_loader = data.DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
    val_loader = data.DataLoader(val_dataset, batch_size=batch_size, shuffle=False)
    model = model.to(device)
    criterion = nn.BCEWithLogitsLoss()
    optimizer = optim.Adam(model.parameters(), lr=lr, weight_decay=1e-5)
    
    for epoch in range(num_epochs):
        model.train()
        train_loss = 0
        for seq1, seq2, labels in tq.tqdm(train_loader, desc=f"Epoch {epoch+1}/{num_epochs}"):
            seq1, seq2, labels = seq1.to(device), seq2.to(device), labels.to(device)
            optimizer.zero_grad()
            outputs = model(seq1, seq2)
            loss = criterion(outputs, labels)
            loss.backward()
            torch.nn.utils.clip_grad_norm_(model.parameters(), max_norm=1.0)
            optimizer.step()
            train_loss += loss.item() * seq1.size(0)
        train_loss /= len(train_dataset)
        
        model.eval()
        val_loss = 0
        with torch.no_grad():
            for seq1, seq2, labels in val_loader:
                seq1, seq2, labels = seq1.to(device), seq2.to(device), labels.to(device)
                outputs = model(seq1, seq2)
                loss = criterion(outputs, labels)
                val_loss += loss.item() * seq1.size(0)
        val_loss /= len(val_dataset)
        
        print(f"Epoch {epoch+1}/{num_epochs}, Train Loss: {train_loss:.4f}, Val Loss: {val_loss:.4f}")

    torch.save(model.state_dict(), 'best_model.pt')

# 预测函数
def evaluate_model(model, test_dataset, batch_size=64):
    test_loader = data.DataLoader(test_dataset, batch_size=batch_size, shuffle=False)
    model = model.to(device)
    model.eval()
    predictions = []
    with torch.no_grad():
        for seq1, seq2 in tq.tqdm(test_loader, desc="生成预测"):
            seq1, seq2 = seq1.to(device), seq2.to(device)
            outputs = model(seq1, seq2)
            probs = torch.sigmoid(outputs)
            predictions.extend(probs.cpu().numpy())
    return predictions

# 主程序
if __name__ == "__main__":
    time_stamps.append(TimeStamp("加载数据开始").show())
    train_dataset, val_dataset, test_dataset = load_all_data()
    time_stamps.append(TimeStamp("加载数据结束").show())
    
    model = SimilarityModel(input_dim=1, hidden_dim=128, num_layers=1, dropout=0.2)
    
    time_stamps.append(TimeStamp("训练模型开始").show())
    train_model(model, train_dataset, val_dataset, num_epochs=10, batch_size=64, lr=1e-3)
    time_stamps.append(TimeStamp("训练模型结束").show())
    
    time_stamps.append(TimeStamp("预测开始").show())
    predictions = evaluate_model(model, test_dataset, batch_size=64)
    time_stamps.append(TimeStamp("预测结束").show())
    
    with open('predictions.tsv', 'w', encoding='utf-8') as f:
        for pred in predictions:
            f.write(f"{pred:.6f}\n")
    print("预测结果已保存至 'predictions.tsv'")
    
    show_time_stamps()