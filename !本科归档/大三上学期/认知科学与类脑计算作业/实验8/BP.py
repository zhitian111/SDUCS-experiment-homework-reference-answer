import numpy as np

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(y):
    return y * (1 - y)

x = np.array([[0.35], [0.9]])
target = np.array([[0.5]])

input_size = 2
hidden_size = 2
output_size = 1
learning_rate = 0.5
max_epochs = 100000

np.random.seed(42)
W1 = np.random.randn(hidden_size, input_size) * 0.5
b1 = np.zeros((hidden_size, 1))
W2 = np.random.randn(output_size, hidden_size) * 0.5
b2 = np.zeros((output_size, 1))

for epoch in range(max_epochs):
    z1 = W1 @ x + b1
    a1 = sigmoid(z1)
    z2 = W2 @ a1 + b2
    y = sigmoid(z2)
    loss = 0.5 * np.sum((target - y) ** 2)

    if loss < 0.01:
        print(f"Converged at epoch {epoch}, loss={loss:.6f}, output={y.ravel()[0]:.6f}")
        break

    delta_output = (y - target) * sigmoid_derivative(y)
    delta_hidden = (W2.T @ delta_output) * sigmoid_derivative(a1)

    dW2 = delta_output @ a1.T
    db2 = delta_output
    dW1 = delta_hidden @ x.T
    db1 = delta_hidden

    W2 -= learning_rate * dW2
    b2 -= learning_rate * db2
    W1 -= learning_rate * dW1
    b1 -= learning_rate * db1

print("Final Output:", y.ravel()[0])
print("Final Loss:", loss)
