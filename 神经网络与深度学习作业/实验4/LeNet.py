import numpy as np
from tqdm import tqdm
from torchvision import datasets, transforms
import torch

MNIST_PATH = r'F:\DATASET\MNIST\mnist_dataset_dir'

transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.1307,), (0.3081,))
])

batch_size = 64

train_data = datasets.MNIST(root=MNIST_PATH,
                            train=True,
                            transform=transform,
                            download=True)
test_data = datasets.MNIST(root=MNIST_PATH,
                           train=False,
                           transform=transform,
                           download=True)

train_gen = torch.utils.data.DataLoader(train_data,
                                        batch_size=batch_size,
                                        shuffle=True)
test_gen = torch.utils.data.DataLoader(test_data,
                                       batch_size=batch_size,
                                       shuffle=False)


class AsymmetricConv2d(torch.nn.Module):
    def __init__(self, in_channels, out_channels, kernel_size, connection_table):
        super().__init__()
        self.connection_table = connection_table
        self.k = kernel_size

        self.convs = torch.nn.ModuleList([
            torch.nn.Conv2d(len(connection_table[i]), 1, kernel_size=self.k)
            for i in range(out_channels)
        ])

    def forward(self, x):
        outputs = []
        for i, conv in enumerate(self.convs):
            in_idx = self.connection_table[i]
            subset = x[:, in_idx, :, :]
            y = conv(subset)
            outputs.append(y)
        return torch.cat(outputs, dim=1)



class LeNet(torch.nn.Module):
    def __init__(self, num_classes=10):
        super(LeNet, self).__init__()
        self.conv1 = torch.nn.Conv2d(kernel_size=5, padding=2,in_channels=1, out_channels=6)
        self.s2 = torch.nn.AvgPool2d(kernel_size=2, stride=2)
        # self.conv3 = torch.nn.Conv2d(kernel_size=5, padding=0, in_channels=6, out_channels=16)

        connection_table = [
            [0,1,2], [1,2,3], [2,3,4], [3,4,5],
            [0,4,5], [0,1,5],
            [0,1,2,3], [1,2,3,4], [2,3,4,5],
            [0,3,4,5], [0,1,4,5], [0,1,2,5],
            [0,2,3,4,5], [0,1,3,4,5], [0,1,2,4,5],
            [0,1,2,3,4,5]
        ]
        self.conv3 = AsymmetricConv2d(in_channels=6, out_channels=16, kernel_size=5, connection_table=connection_table)

        self.s4 = torch.nn.AvgPool2d(kernel_size=2, stride=2)
        self.fc1 = torch.nn.Linear(in_features=16 * 5 * 5, out_features=120)
        self.fc2 = torch.nn.Linear(in_features=120, out_features=84)
        self.fc3 = torch.nn.Linear(in_features=84, out_features=num_classes)

        self.get_layer_info(torch.randn(1, 1, 28, 28))

    def get_layer_info(self, x):
        x = self.conv1(x)
        print(f"Conv1 output shape: {x.shape}")
        x = torch.nn.functional.relu(x)
        print(f"ReLU1 output shape: {x.shape}")
        x = self.s2(x)
        print(f"AvgPool1 output shape: {x.shape}")
        x = self.conv3(x)
        print(f"Conv2 output shape: {x.shape}")
        x = torch.nn.functional.relu(x)
        print(f"ReLU2 output shape: {x.shape}")
        x = self.s4(x)
        print(f"AvgPool2 output shape: {x.shape}")
        x = torch.flatten(x)
        print(f"Flatten output shape: {x.shape}")
        x = self.fc1(x)
        print(f"FC1 output shape: {x.shape}")
        x = torch.nn.functional.relu(x)
        print(f"ReLU3 output shape: {x.shape}")
        x = self.fc2(x)
        print(f"FC2 output shape: {x.shape}")
        x = torch.nn.functional.relu(x)
        print(f"ReLU4 output shape: {x.shape}")
        x = self.fc3(x)
        print(f"FC3 output shape: {x.shape}")
        return x

    def forward(self, x):
        x = self.conv1(x)
        x = torch.nn.functional.relu(x)
        x = self.s2(x)
        x = self.conv3(x)
        x = torch.nn.functional.relu(x)
        x = self.s4(x)
        x = torch.flatten(x, 1)
        x = self.fc1(x)
        x = torch.nn.functional.relu(x)
        x = self.fc2(x)
        x = torch.nn.functional.relu(x)
        x = self.fc3(x)
        return x

model = LeNet()

criterion = torch.nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(model.parameters(), lr=0.001)

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model.to(device)
print(f"训练设备: {device}")

for epoch in range(10):
    running_loss = 0.0
    for i, data in enumerate(tqdm(train_gen), 0):
        inputs, labels = data
        inputs, labels = inputs.to(device), labels.to(device)
        optimizer.zero_grad()
        outputs = model(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()
        running_loss += loss.item()
    print(f"Epoch {epoch+1} loss: {running_loss/len(train_gen)}")


correct = 0
total = 0
model.eval()
for i, data in enumerate(tqdm(test_gen), 0):
    inputs, labels = data
    inputs, labels = inputs.to(device), labels.to(device)
    outputs = model(inputs)
    _, predicted = torch.max(outputs.data, 1)
    total += labels.size(0)
    correct += (predicted == labels).sum().item()

print(f"Accuracy of the network on the 10000 test images: {100 * correct / total}%")
