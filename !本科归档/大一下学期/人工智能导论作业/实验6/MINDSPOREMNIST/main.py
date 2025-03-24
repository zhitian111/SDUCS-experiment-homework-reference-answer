import mindspore
import numpy
import numpy as np
from mindspore.dataset import vision
from mindspore.dataset import MnistDataset, GeneratorDataset
import matplotlib.pyplot as plt
from mindspore.dataset import transforms, vision, text
from mindspore import nn,ops

# 参数设置
n_epochs = 3                    #训练次数
batch_size_train = 64           #训练时单次抓取样本数
batch_size_test = 1000          #测试时单次抓取样本数
learning_rate = 0.01            #学习率
momentum = 0.5                  #梯度下降动量
log_interval = 10               #多少个 batch 打印一次训练状态
lay1_node_cnt = 512             #中间层1节点个数
lay2_node_cnt = 512             #中间层2节点个数
# 初始化数据集
#加载
path="F:\\DATASET\\MNIST\\mnist_dataset_dir"
train_data = MnistDataset(path,shuffle=True)
test_data = MnistDataset(path,shuffle=True)
# train_data = train_data.batch(batch_size_train)
# test_data = test_data.batch(batch_size_test)

print(type(train_data))
print(type(test_data))

#可视化部分
def visualize(dataset):
    figure = plt.figure(figsize=(4, 4))
    cols, rows = 3, 3

    plt.subplots_adjust(wspace=0.5, hspace=0.5)

    for idx, (image, label) in enumerate(dataset.create_tuple_iterator()):
        figure.add_subplot(rows, cols, idx + 1)
        plt.title(int(label))
        plt.axis("off")
        plt.imshow(image.asnumpy().squeeze(), cmap="gray")
        if idx == cols * rows - 1:
            break
    plt.show()
# visualize(train_data)

image, label = next(train_data.create_tuple_iterator())
print(image.shape, image.dtype)


# transforms部分
#更改数据类型(与实现transform对象等价)
composed = transforms.Compose(
    [
        vision.Rescale(1.0 / 255.0, 0),
        vision.Normalize(mean=(0.1307,), std=(0.3081,)),
        vision.HWC2CHW()
    ]
)
train_data = train_data.map(operations=composed, input_columns="image")
# train_data = train_data.map(vision.ToTensor())
test_data = test_data.map(operations=composed,input_columns="image")
# test_data = test_data.map(vision.ToTensor())
print(type(train_data))
print(type(test_data))

image, label = next(train_data.create_tuple_iterator())
print(image.shape, image.dtype)


# for i ,(j,k) in enumerate(train_data.create_tuple_iterator()):
#     rescaled_image = j.asnumpy()
#     plt.imshow(rescaled_image.squeeze(), cmap="gray")
#     plt.show()
#     input()
#     normalize = vision.Normalize(mean=(0.1307,), std=(0.3081,))
#     normalized_image = normalize(rescaled_image)
#     print(normalized_image)
# train_data = train_data.batch(batch_size=batch_size_train)
# test_data = test_data.batch(batch_size=batch_size_test)

class Network(nn.Cell):
    def __init__(self):
        super().__init__()
        self.flatten = nn.Flatten()
        #相邻两层的节点之间均为全链接
        self.dense_relu_sequential = nn.SequentialCell(
            nn.Dense(28*28, lay1_node_cnt, weight_init="normal", bias_init="zeros"),
            nn.ReLU(),
            nn.Dense(lay1_node_cnt, lay2_node_cnt, weight_init="normal", bias_init="zeros"),
            nn.ReLU(),
            nn.Dense(lay2_node_cnt, 10, weight_init="normal", bias_init="zeros")
        )

    def construct(self, x):
        x = self.flatten(x)
        logits = self.dense_relu_sequential(x)
        return logits
Net = Network()
Net.set_train(train_data)
print(Net)
X = ops.ones((1, 28, 28), mindspore.float32)
logits = Net(X)
print(logits)


# 损失函数
def loss_fn(logits, label):
    labels=[0 for i in range(10)]
    labels[label]=1
    logits = Net(logits)
    pred_probab = nn.Softmax(axis=1)(logits)
    print(pred_probab)
    ans = pred_probab.argmax(1)
    print(f"Predicted class: {ans}")
    loss=0
    print(logits[0])
    for i in range(len(logits[0])):
        loss+=(labels[i]-logits[0][i])**2
    print("loss=",loss)
    return loss

# 梯度函数
def accuracy(function,x,y):
    grad_fn = mindspore.value_and_grad(function, None, weights=Net.trainable_params())
    loss, grads = grad_fn(x,y)
    return loss.asnumpy()


value,shape=next(train_data.create_tuple_iterator())
print(shape)
print(value)
print(loss_fn(value, 1))
print(len(next(train_data.create_tuple_iterator())))
# loss_fn(input_image,label)
#
# flatten = nn.Flatten()
# flat_image = flatten(input_image)
# print(flat_image.shape)

# Define forward function
def forward_fn(data, label):
    logits = Net(data)
    loss = loss_fn(logits, label)
    return loss, logits
optimizer = nn.SGD(Net.trainable_params(), learning_rate=learning_rate)

# Get gradient function
grad_fn = mindspore.value_and_grad(forward_fn, None, optimizer.parameters, has_aux=True)

# Define function of one-step training
def train_step(data, label):
    (loss, _), grads = grad_fn(data, label)
    optimizer(grads)
    return loss

def train_loop(model, dataset):
    size = dataset.get_dataset_size()
    model.set_train()
    for batch, (data, label) in enumerate(dataset.create_tuple_iterator()):
        loss = train_step(data, label)

        if batch % 100 == 0:
            loss, current = loss.asnumpy(), batch
            print(f"loss: {loss:>7f}  [{current:>3d}/{size:>3d}]")
def test_loop(model, dataset, loss_fn):
    num_batches = dataset.get_dataset_size()
    model.set_train(False)
    total, test_loss, correct = 0, 0, 0
    for data, label in dataset.create_tuple_iterator():
        pred = model(data)
        total += len(data)
        test_loss += loss_fn(pred, label).asnumpy()
        correct += (pred.argmax(1) == label).asnumpy().sum()
    test_loss /= num_batches
    correct /= total
    print(f"Test: \n Accuracy: {(100*correct):>0.1f}%, Avg loss: {test_loss:>8f} \n")
loss_fn = nn.CrossEntropyLoss()
optimizer = nn.SGD(Net.trainable_params(), learning_rate=learning_rate)

for i in range(n_epochs):
    print(f"Epoch {i+1}\n-------------------------------")
    train_loop(Net, train_data)
    test_loop(Net, test_data, loss_fn)


mindspore.save_checkpoint(Net, "model.ckpt")




class Network(nn.Cell):
    def __init__(self):
        super().__init__()
        self.flatten = nn.Flatten()
        #相邻两层的节点之间均为全链接
        self.dense_relu_sequential = nn.SequentialCell(
            nn.Dense(28*28, lay1_node_cnt, weight_init="normal", bias_init="zeros"),
            nn.ReLU(),
            nn.Dense(lay1_node_cnt, lay2_node_cnt, weight_init="normal", bias_init="zeros"),
            nn.ReLU(),
            nn.Dense(lay2_node_cnt, 10, weight_init="normal", bias_init="zeros")
        )

    def construct(self, x):
        x = self.flatten(x)
        logits = self.dense_relu_sequential(x)
        return logits

model = Network()
param_dict = mindspore.load_checkpoint("model.ckpt")
param_not_load, _ = mindspore.load_param_into_net(model, param_dict)
print(param_not_load)
