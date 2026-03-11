from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
import torch.nn as nn
import torch.optim
import numpy as np

# 下载/加载数据集

iris = load_iris()

# 标准化数据

scaler = StandardScaler()
iris.data = scaler.fit_transform(iris.data)

# 划分训练集和测试集

x_train, x_test, y_train, y_test = train_test_split(iris.data, iris.target, test_size=0.2, random_state=11,stratify=iris.target)


hidden_size1 = 64
hidden_size2 = 32
learning_rate = 0.005
epochs = 100
batch_size = 32
test_epochs = 10
test_batch_size = 16
class FCNN(nn.Module):
    def __init__(self, input_size=4, hidden_size1=hidden_size1, hidden_size2=hidden_size2, output_size=3):
        super(FCNN, self).__init__()
        self.fc1 = nn.Linear(input_size, hidden_size1)
        self.fc2 = nn.Linear(hidden_size1, hidden_size2)
        self.fc3 = nn.Linear(hidden_size2, output_size)
        self.relu = nn.ReLU()
        self.dropout = nn.Dropout(0.2)

    def forward(self, x):
        x = self.fc1(x)
        x = self.relu(x)
        x = self.dropout(x)
        x = self.fc2(x)
        x = self.relu(x)
        x = self.dropout(x)
        x = self.fc3(x)
        return x

model = FCNN()
criterion = nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)


def train_loader(x_train, y_train, batch_size=batch_size):
    x_train = torch.from_numpy(x_train).float()
    y_train = torch.from_numpy(y_train).long()
    dataset = torch.utils.data.TensorDataset(x_train, y_train)
    loader = torch.utils.data.DataLoader(dataset, batch_size=batch_size, shuffle=True)
    return loader

def test_loader(x_test, y_test, batch_size=test_batch_size):
    x_test = torch.from_numpy(x_test).float()
    y_test = torch.from_numpy(y_test).long()
    dataset = torch.utils.data.TensorDataset(x_test, y_test)
    loader = torch.utils.data.DataLoader(dataset, batch_size=batch_size, shuffle=True)
    return loader

if __name__ == '__main__':

    train_loader = train_loader(x_train, y_train)
    for epoch in range(epochs):
        for i, (inputs, labels) in enumerate(train_loader):
            optimizer.zero_grad()
            outputs = model(inputs)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()
        # if (epoch+1) % 10 == 0:
            print('Epoch [{}/{}], Loss: {:.4f}'.format(epoch+1, epochs, loss.item()))
    # 预测
    model.eval()
    test_correct = 0
    test_loader = test_loader(x_test, y_test)
    test_results = []
    with torch.no_grad():
        for test_epoch in range(test_epochs):
            for inputs, labels in test_loader:
                outputs = model(inputs)

                test_correct = 0
                _, predicted = torch.max(outputs.data, 1)
                test_correct += (predicted == labels).sum().item()
                print(outputs)
                print(predicted)
                print(labels)
                print("{}/{}".format(test_correct, len(labels)))
                print('Epoch [{}/{}], Accuracy: {:.8f}%'.format(test_epoch+1, test_epochs, 100 * test_correct / len(labels)))
                test_results.append(100 * test_correct / len(labels))
    print('Test Accuracy: {:.8f}%'.format(np.mean(test_results)))
