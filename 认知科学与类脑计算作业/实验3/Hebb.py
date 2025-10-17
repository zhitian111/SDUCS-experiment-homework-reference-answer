# 数字点阵
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
cmap = mcolors.ListedColormap(['white', 'black'])
bounds = [-1.5, 0, 1.5]
norm = mcolors.BoundaryNorm(bounds, cmap.N)
one = np.array([[-1, -1, 1, -1, -1],
               [-1,  1, 1, -1, -1],
               [-1, -1, 1, -1, -1],
               [-1, -1, 1, -1, -1],
               [-1, -1, 1, -1, -1],
               [-1, 1, 1, 1, -1]]).flatten()
two = np.array([[1, 1, 1, 1, 1],
                [-1, -1, -1, -1, 1],
                [-1, -1, -1, -1, 1],
                [1, 1, 1, 1, 1],
                [1, -1, -1, -1, -1],
               [1, 1, 1, 1, 1]]).flatten()
zero = np.array([[1, 1, 1, 1, 1],
                 [1, -1, -1, -1, 1],
                 [1, -1, -1, -1, 1],
                 [1, -1, -1, -1, 1],
                 [1, -1, -1, -1, 1],
                 [1, 1, 1, 1, 1]]).flatten()
def one_dim_array_to_two_dim(array):
    array = array.reshape(6, 5)
    return array


def save_number_image(number, label, path):
    plt.figure(figsize=(3, 5))
    plt.imshow(number, cmap=cmap, norm=norm)
    plt.title(label)
    plt.axis('off')
    plt.savefig(path)
    plt.close()

def softmax(x, axis=-1):
    """稳定版 softmax，支持任意轴"""
    x_max = np.max(x, axis=axis, keepdims=True)  # 防溢出
    exp = np.exp(x - x_max)
    return exp / np.sum(exp, axis=axis, keepdims=True)

# 定义Hebb神经网络
class HebbNet:
    def __init__(self, learning_rate=0.1, epochs=1000, train_data_set=None, train_label_set=None):
        self.learning_rate = learning_rate
        self.epochs = epochs
        self.train_data_set = train_data_set
        self.train_label_set = train_label_set
        if train_data_set is not None and train_label_set is not None:
            self.weights = np.zeros((len(train_label_set[0]), len(train_data_set[0])))
        # print("初始化权重为：", self.weights)

    def train_no_oja(self):
        for epoch in range(self.epochs):
            for i in range(len(self.train_data_set)):
                self.weights += self.learning_rate * np.outer(self.train_label_set[i], self.train_data_set[i])
            # print("第", epoch, "轮权重为：", self.weights)

    def train_yes_oja(self):
        for epoch in range(self.epochs):
            for i in range(len(self.train_data_set)):
                x = self.train_data_set[i]
                t = self.train_label_set[i]
                for j in range(len(t)):
                    if t[j] != 0:
                        y_post = t[j]  # 目标作为后突触活动，通常为 1
                        activation = np.dot(self.weights[j], x)  # 前向计算激活
                        self.weights[j] += self.learning_rate * y_post * (x - activation * self.weights[j])
    def predict(self, input_data):
        return softmax(np.matmul(self.weights, input_data))

def random_broke_number(number, broke_count=-1):
    if broke_count == -1:
        broke_count = np.random.randint(0, len(number) / 2)
    for i in range(broke_count):
        index = np.random.randint(0, len(number))
        number[index] = -1 if number[index] == 1 else 1
    return number

if __name__ == '__main__':
    train_data_set = [one, two, zero]
    train_label_set = [[0,1,0], [0,0,1], [1,0,0]]
    hebb_net = HebbNet(train_data_set=train_data_set, train_label_set=train_label_set, epochs=100)
    hebb_net.train_yes_oja()
    print(hebb_net.weights)
    broken_one = random_broke_number(one, 3).flatten()
    broken_two = random_broke_number(two, 3).flatten()
    broken_zero = random_broke_number(zero, 3).flatten()

    save_number_image(one_dim_array_to_two_dim(broken_one), 'broken_one', 'broken_1.png')
    save_number_image(one_dim_array_to_two_dim(broken_two), 'broken_two', 'broken_2.png')
    save_number_image(one_dim_array_to_two_dim(broken_zero), 'broken_zero', 'broken_0.png')

    print(hebb_net.predict(broken_zero))
    print(hebb_net.predict(broken_one))
    print(hebb_net.predict(broken_two))