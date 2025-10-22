import torch
import torch.nn as nn
import torch.optim as optim
from torchvision import datasets, transforms
import matplotlib.pyplot as plt

transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.5,), (0.5,))
])

train_data = datasets.MNIST(root='F:\\DATASET\\MNIST\\mnist_dataset_dir', train=True, transform=transform, download=True)
test_data = datasets.MNIST(root='F:\\DATASET\\MNIST\\mnist_dataset_dir', train=False, transform=transform, download=True)

train_loader = torch.utils.data.DataLoader(train_data, batch_size=256, shuffle=True)
test_loader = torch.utils.data.DataLoader(test_data, batch_size=256, shuffle=False)

class TopoICA(nn.Module):
    def __init__(self, input_dim=784, n_components=64, n_classes=10):
        super(TopoICA, self).__init__()
        self.W = nn.Parameter(torch.randn(input_dim, n_components) * 0.01)
        self.classifier = nn.Linear(n_components, n_classes)

    def forward(self, x):
        s = torch.matmul(x, self.W)
        logits = self.classifier(s)
        return s, logits

    def reconstruct(self, s):
        return torch.matmul(s, self.W.T)

def topo_loss(W, lambda_topo=0.1):
    diff = W[1:] - W[:-1]
    return lambda_topo * torch.mean(diff ** 2)

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model = TopoICA().to(device)
optimizer = optim.Adam(model.parameters(), lr=1e-3)
criterion_cls = nn.CrossEntropyLoss()

def ica_loss(x, x_hat):
    recon = torch.mean((x - x_hat) ** 2)
    sparsity = torch.mean(torch.abs(x_hat))
    return recon + 0.01 * sparsity

num_epochs = 5
for epoch in range(num_epochs):
    model.train()
    total_loss = 0
    for images, labels in train_loader:
        images = images.view(images.size(0), -1).to(device)
        labels = labels.to(device)

        s, logits = model(images)
        x_hat = model.reconstruct(s)

        loss_unsup = ica_loss(images, x_hat) + topo_loss(model.W)
        loss_sup = criterion_cls(logits, labels)
        loss = loss_unsup + 0.1 * loss_sup

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        total_loss += loss.item()

    print(f"Epoch [{epoch+1}/{num_epochs}], Loss: {total_loss/len(train_loader):.4f}")

model.eval()
correct = 0
total = 0
with torch.no_grad():
    for images, labels in test_loader:
        images = images.view(images.size(0), -1).to(device)
        labels = labels.to(device)
        _, logits = model(images)
        pred = torch.argmax(logits, dim=1)
        correct += (pred == labels).sum().item()
        total += labels.size(0)

acc = correct / total
print(f"Test Accuracy: {acc:.4f}")

W = model.W.detach().cpu().T
fig, axes = plt.subplots(8, 8, figsize=(8, 8))
for i, ax in enumerate(axes.flat):
    ax.imshow(W[i].reshape(28, 28), cmap='gray')
    ax.axis('off')
plt.suptitle("Learned Independent Components (TopoICA)")
plt.show()
