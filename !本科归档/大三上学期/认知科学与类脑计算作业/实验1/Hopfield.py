
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
    return number

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


def one_dim_array_to_two_dim(array):
    array = array.reshape(6, 5)
    return array

def shuffle_array(array):
    np.random.shuffle(array)
    return array


class Hopfield:
    def __init__(self, number_arrays):
        self.number_arrays = number_arrays
        self.weights = np.zeros((len(number_arrays[0]), len(number_arrays[0])))
    def print_weights(self):
        print(self.weights)

    def train(self):
        for i in self.number_arrays:
            for j in range(len(i)):
                for k in range(len(i)):
                    self.weights[j][k] += i[j] * i[k]
        print(self.weights)

    def recall(self, input_array, max_loop=1000):
        output_array = np.zeros(len(input_array))
        tem_array = input_array.copy()
        energy = 0
        loop_count = 0
        while True:
            loop_count += 1
            changed = False
            random_index = [i for i in range(len(tem_array))]

            random_index = shuffle_array(random_index)


            print(random_index)
            for loop in range(len(tem_array)):
                energy = 0
                i = random_index[loop]
                for j in range(len(tem_array)):
                    energy += self.weights[i][j] * tem_array[j]

                if energy > 0:
                    if tem_array[i] != 1:
                        changed = True
                        print("changed", i)
                    else:
                        changed = changed
                    tem_array[i] = 1
                elif energy < 0:
                    if tem_array[i] != -1:
                        changed = True
                        print("changed", i)
                    else:
                        changed = changed
                    tem_array[i] = -1
            # plot_number(one_dim_array_to_two_dim(tem_array), 'tem_array')


            if not changed:
                output_array = tem_array
                break

            if loop_count > max_loop:
                break
        return output_array

def random_broke_number(number, broke_count = -1):
    if broke_count == -1:
        broke_count = np.random.randint(0, len(number) / 2)
    for i in range(broke_count):
        index = np.random.randint(0, len(number))
        number[index] = -1 if number[index] == 1 else 1
    return number



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
    # local_number_arrays = [one, two, three, four, five, six, seven, eight, nine, zero]
    local_number_arrays = [one, two, three, four]
    hopfield = Hopfield(local_number_arrays)
    hopfield.print_weights()
    hopfield.train()
    hopfield.print_weights()
    
    broken_one = random_broke_number(one, 3)
    broken_two = random_broke_number(two, 3)
    broken_three = random_broke_number(three, 3)
    broken_four = random_broke_number(four, 3)
    broken_five = random_broke_number(five, 3)
    broken_six = random_broke_number(six, 3)
    broken_seven = random_broke_number(seven, 3)
    broken_eight = random_broke_number(eight, 3)
    broken_nine = random_broke_number(nine, 3)
    broken_zero = random_broke_number(zero, 3)
    #
    # save_number_image(one_dim_array_to_two_dim(broken_one), 'broken_one', 'broken_1.png')
    # save_number_image(one_dim_array_to_two_dim(broken_two), 'broken_two', 'broken_2.png')
    # save_number_image(one_dim_array_to_two_dim(broken_three), 'broken_three', 'broken_3.png')
    # save_number_image(one_dim_array_to_two_dim(broken_four), 'broken_four', 'broken_4.png')
    # save_number_image(one_dim_array_to_two_dim(broken_five), 'broken_five', 'broken_5.png')
    # save_number_image(one_dim_array_to_two_dim(broken_six), 'broken_six', 'broken_6.png')
    # save_number_image(one_dim_array_to_two_dim(broken_seven), 'broken_seven', 'broken_7.png')
    # save_number_image(one_dim_array_to_two_dim(broken_eight), 'broken_eight', 'broken_8.png')
    # save_number_image(one_dim_array_to_two_dim(broken_nine), 'broken_nine', 'broken_9.png')
    # save_number_image(one_dim_array_to_two_dim(broken_zero), 'broken_zero', 'broken_0.png')
    
    fixed_one = hopfield.recall(broken_one)
    fixed_two = hopfield.recall(broken_two)
    fixed_three = hopfield.recall(broken_three)
    fixed_four = hopfield.recall(broken_four)
    fixed_five = hopfield.recall(broken_five)
    fixed_six = hopfield.recall(broken_six)
    fixed_seven = hopfield.recall(broken_seven)
    fixed_eight = hopfield.recall(broken_eight)
    fixed_nine = hopfield.recall(broken_nine)
    fixed_zero = hopfield.recall(broken_zero)

    # plot_number(one_dim_array_to_two_dim(fixed_one), 'fixed_one')
    plot_number(one_dim_array_to_two_dim(fixed_two), 'fixed_two')
    # plot_number(one_dim_array_to_two_dim(fixed_three), 'fixed_three')
    # plot_number(one_dim_array_to_two_dim(fixed_four), 'fixed_four')
