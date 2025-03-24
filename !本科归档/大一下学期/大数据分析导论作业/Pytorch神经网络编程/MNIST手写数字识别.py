from torchvision import datasets
import torchvision
import torch
import matplotlib.pyplot as plt
import torch.nn as nn               #用于神经网络
import torch.nn.functional as F
import torch.optim as optim
# 模型可调参数
n_epochs = 3                    #训练次数
batch_size_train = 64           #单次抓取样本数
batch_size_test = 1000          #单次抓取样本数
learning_rate = 0.01            #学习率
momentum = 0.5                  #梯度下降动量
log_interval = 10               #多少个 batch 打印一次训练状态
random_seed = 1                 #随机种子
torch.manual_seed(random_seed)  #随机种子设置



train_data_path="F:\\DATASET\\MNIST\\mnist_data\\train_data"
test_data_path="F:\\DATASET\\MNIST\\mnist_data\\test_data"
data_path="F:\\DATASET\\MNIST\\mnist_data"
# 加载MNIST数据集
train_loader = torch.utils.data.DataLoader(
    torchvision.datasets.MNIST(data_path, train=True, download=True,
                               transform=torchvision.transforms.Compose([
                                   torchvision.transforms.ToTensor(),
                                   torchvision.transforms.Normalize(
                                       (0.1307,), (0.3081,))
                               ])),
                                batch_size=batch_size_train, shuffle=True)
test_loader = torch.utils.data.DataLoader(
    torchvision.datasets.MNIST(data_path, train=False, download=True,
                               transform=torchvision.transforms.Compose([
                                   torchvision.transforms.ToTensor(),
                                   torchvision.transforms.Normalize(
                                       (0.1307,), (0.3081,))
                               ])),
    batch_size=batch_size_test, shuffle=True)








# 测试用可视化
# examples = enumerate(test_loader)
# batch_idx, (example_data, example_targets) = next(examples)
# print(example_targets)
# print(example_data.shape)
#
# fig = plt.figure()
# for i in range(6):
#   plt.subplot(2,3,i+1)
#   plt.tight_layout()
#   plt.imshow(example_data[i][0], cmap='gray', interpolation='none')
#   plt.title("Label: {}".format(example_targets[i]))
#   plt.xticks([])
#   plt.yticks([])
# plt.show()