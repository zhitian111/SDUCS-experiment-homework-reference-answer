import matplotlib.pyplot as plt
from torchvision import datasets
import time
train_data_path="F:\\DATASET\\MNIST\\mnist_data\\train_data"
test_data_path="F:\\DATASET\\MNIST\\mnist_data\\test_data"
data_path="F:\\DATASET\\MNIST\\mnist_data"
# 加载MNIST数据集
mnist_train = datasets.MNIST(root=data_path, train=True,download=False)
mnist_test = datasets.MNIST(root=data_path, train=False,download=False)

# 遍历并保存训练集中的图像
for i, (image, label) in enumerate(mnist_train):
    # 创建一个新的图像并绘制MNIST图像
    plt.figure()
    plt.imshow(image, cmap='gray')
    plt.title('Label: {}'.format(label))
    plt.axis('off')
    time.sleep(0.00001)
    # 保存图像
    plt.savefig('F:\\DATASET\\MNIST\\image\\train_image\\mnist_train_{}.png'.format(i))
    plt.close()

# 遍历并保存测试集中的图像
for i, (image, label) in enumerate(mnist_test):
    # 创建一个新的图像并绘制MNIST图像
    plt.figure()
    plt.imshow(image, cmap='gray')
    plt.title('Label: {}'.format(label))
    plt.axis('off')
    time.sleep(0.00001)
    # 保存图像
    plt.savefig('F:\\DATASET\\MNIST\\image\\test_image\\mnist_test_{}.png'.format(i))
    plt.close()