import numpy as np




class dataset:
    def __init__(self, data, label):
        self.data = data
        self.label = label


and_dataset = dataset(np.array([[0,0],[0,1],[1,0],[1,1]]), np.array([0,0,0,1]))
or_dataset = dataset(np.array([[0,0],[0,1],[1,0],[1,1]]), np.array([0,1,1,1]))
not_dataset = dataset(np.array([[0],[1]]), np.array([1,0]))
xor_dataset = dataset(np.array([[0,0],[0,1],[1,0],[1,1]]), np.array([0,1,1,0]))




learning_rate = 0.1
epochs = 1000

def sigmoid(x):
    return 1/(1+np.exp(-x))

class Perceptron:
    def __init__(self, dataset, learning_rate=learning_rate, epochs=epochs):
        self.dataset = dataset
        self.learning_rate = learning_rate
        self.epochs = epochs
        self.weights = np.random.rand(len(dataset.data[0]))
        self.bias = np.random.rand(1)

    def forward(self, x):
        z = np.dot(x, self.weights)
        return sigmoid(z + self.bias)

    def train(self):
        for epoch in range(self.epochs):
            for x, y in zip(self.dataset.data, self.dataset.label):
                y_pred = self.forward(x)
                error = y - y_pred
                self.weights += self.learning_rate * error * x
                self.bias += self.learning_rate * error

    def predict(self, x):
        y_pred = self.forward(x)
        if y_pred >= 0.5:
            return 1
        else:
            return 0

and_perceptron = Perceptron(and_dataset)
or_perceptron = Perceptron(or_dataset)
xor_perceptron = Perceptron(xor_dataset)
not_perceptron = Perceptron(not_dataset)


and_perceptron.train()
or_perceptron.train()
xor_perceptron.train()
not_perceptron.train()

print("AND Perceptron")
print("{} -> {}".format(and_dataset.data[0], and_perceptron.predict(and_dataset.data[0])))
print("{} -> {}".format(and_dataset.data[1], and_perceptron.predict(and_dataset.data[1])))
print("{} -> {}".format(and_dataset.data[2], and_perceptron.predict(and_dataset.data[2])))
print("{} -> {}".format(and_dataset.data[3], and_perceptron.predict(and_dataset.data[3])))

print("OR Perceptron")
print("{} -> {}".format(or_dataset.data[0], or_perceptron.predict(or_dataset.data[0])))
print("{} -> {}".format(or_dataset.data[1], or_perceptron.predict(or_dataset.data[1])))
print("{} -> {}".format(or_dataset.data[2], or_perceptron.predict(or_dataset.data[2])))
print("{} -> {}".format(or_dataset.data[3], or_perceptron.predict(or_dataset.data[3])))

print("XOR Perceptron")
print("{} -> {}".format(xor_dataset.data[0], xor_perceptron.predict(xor_dataset.data[0])))
print("{} -> {}".format(xor_dataset.data[1], xor_perceptron.predict(xor_dataset.data[1])))
print("{} -> {}".format(xor_dataset.data[2], xor_perceptron.predict(xor_dataset.data[2])))
print("{} -> {}".format(xor_dataset.data[3], xor_perceptron.predict(xor_dataset.data[3])))

print("NOT Perceptron")
print("{} -> {}".format(not_dataset.data[0], not_perceptron.predict(not_dataset.data[0])))
print("{} -> {}".format(not_dataset.data[1], not_perceptron.predict(not_dataset.data[1])))
print("End")