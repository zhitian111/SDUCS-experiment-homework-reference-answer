
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
cmap = mcolors.ListedColormap(['white', 'black'])
bounds = [-1.5, 0, 1.5]
norm = mcolors.BoundaryNorm(bounds, cmap.N)
# 数字点阵
import numpy as np

one = np.array([[-1, -1, 1, -1, -1],
               [-1,  1, 1, -1, -1],
               [-1, -1, 1, -1, -1],
               [-1, -1, 1, -1, -1],
               [-1, -1, 1, -1, -1],
               [-1, 1, 1, 1, -1]])
two = np.array([[1, 1, 1, 1, 1],
                [-1, -1, -1, -1, 1],
                [-1, -1, -1, -1, 1],
                [1, 1, 1, 1, 1],
                [1, -1, -1, -1, -1],
               [1, 1, 1, 1, 1]])
three = np.array([[1, 1, 1, 1, 1],
                [-1, -1, -1, -1, 1],
                [1, 1, 1, 1, 1],
                [-1, -1, -1, -1, 1],
                [-1, -1, -1, -1, 1],
                [1, 1, 1, 1, 1]])
four = np.array([[1, -1, -1, -1, 1],
                 [1, -1, -1, -1, 1],
                 [1, -1, -1, -1, 1],
                 [1, 1, 1, 1, 1],
                 [-1, -1, -1, -1, 1],
                 [-1, -1, -1, -1, 1]])
five = np.array([[1, 1, 1, 1, 1],
                 [1, -1, -1, -1, -1],
                 [1, 1, 1, 1, 1],
                 [-1, -1, -1, -1, 1],
                 [-1, -1, -1, -1, 1],
                 [1, 1, 1, 1, 1]])
six = np.array([[1, 1, 1, 1, 1],
                [1, -1, -1, -1, -1],
                [1, 1, 1, 1, 1],
                [1, -1, -1, -1, 1],
                [1, -1, -1, -1, 1],
                [1, 1, 1, 1, 1]])
seven = np.array([[1, 1, 1, 1, 1],
                [-1, -1, -1, -1, 1],
                [-1, -1, -1, 1, -1],
                [-1, -1, 1, -1, -1],
                [-1, 1, -1, -1, -1],
                [1, -1, -1, -1, -1]])
eight = np.array([[1, 1, 1, 1, 1],
                [1, -1, -1, -1, 1],
                [1, 1, 1, 1, 1],
                [1, -1, -1, -1, 1],
                [1, -1, -1, -1, 1],
                [1, 1, 1, 1, 1]])
nine = np.array([[1, 1, 1, 1, 1],
                 [1, -1, -1, -1, 1],
                 [1, 1, 1, 1, 1],
                 [-1, -1, -1, -1, 1],
                 [-1, -1, -1, -1, 1],
                 [1, 1, 1, 1, 1]])
zero = np.array([[1, 1, 1, 1, 1],
                 [1, -1, -1, -1, 1],
                 [1, -1, -1, -1, 1],
                 [1, -1, -1, -1, 1],
                 [1, -1, -1, -1, 1],
                 [1, 1, 1, 1, 1]])

def plot_number(number, label='number'):
    plt.figure(figsize=(3, 5))
    plt.imshow(number, cmap=cmap, norm=norm)
    plt.title(label)
    plt.axis('off')
    plt.show()

def save_number_image(number, label, path):
    plt.figure(figsize=(3, 5))
    plt.imshow(number, cmap=cmap, norm=norm)
    plt.title(label)
    plt.axis('off')
    plt.savefig(path)
    plt.close()

def two_dim_array_to_one_dim(array):
    array = array.flatten()
    return array

if __name__ == '__main__':
    # plot_number(one, 'one')
    # plot_number(two, 'two')
    # plot_number(three, 'three')
    # plot_number(four, 'four')
    # plot_number(five, 'five')
    # plot_number(six, 'six')
    # plot_number(seven,'seven')
    # plot_number(eight, 'eight')
    # plot_number(nine, 'nine')
    # plot_number(zero, 'zero')
    # save_number_image(one, 'one', '1.png')
    # save_number_image(two, 'two', '2.png')
    # save_number_image(three, 'three', '3.png')
    # save_number_image(four, 'four', '4.png')
    # save_number_image(five, 'five', '5.png')
    # save_number_image(six, 'six', '6.png')
    # save_number_image(seven,'seven','7.png')
    # save_number_image(eight, 'eight', '8.png')
    # save_number_image(nine, 'nine', '9.png')
    # save_number_image(zero, 'zero', '0.png')
    one = two_dim_array_to_one_dim(one)
    two = two_dim_array_to_one_dim(two)
    three = two_dim_array_to_one_dim(three)
    four = two_dim_array_to_one_dim(four)
    five = two_dim_array_to_one_dim(five)
    six = two_dim_array_to_one_dim(six)
    seven = two_dim_array_to_one_dim(seven)
    eight = two_dim_array_to_one_dim(eight)
    nine = two_dim_array_to_one_dim(nine)
    zero = two_dim_array_to_one_dim(zero)
    print(one)
    print(two)
    print(three)
    print(four)
    print(five)
    print(six)
    print(seven)
    print(eight)
    print(nine)
    print(zero)