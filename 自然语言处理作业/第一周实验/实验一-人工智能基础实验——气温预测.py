import csv
import numpy as np
import sklearn.linear_model as lm
import matplotlib.pyplot as plt

exp1_1_test_data = [i for i in np.arange(0, 10, 0.1)]
exp1_1_test_data = [[i] for i in exp1_1_test_data]


def load_exp1_1_data(path="./exp-1.1-data.csv"):
    csv_data = []
    with open(path, newline='') as csvfile:
        csv_reader = csv.reader(csvfile, delimiter=' ')
        for row in csv_reader:
            csv_data.append(row)
    result = []
    result.append(csv_data[0])
    for i in csv_data[1:]:
        result.append([float(i[0]),float(i[1])])
    result_x = [[i[0]] for i in result[1:]]
    result_y = [[i[1]] for i in result[1:]]
    return result_x, result_y


def get_exp1_1_model():
    data_x, data_y = load_exp1_1_data()
    reg = lm.LinearRegression()
    reg.fit(data_x, data_y)
    return reg



def test_exp1_1():
    reg = get_exp1_1_model()
    print(f"线性回归模型的表达式为：\ny = {reg.coef_[0][0]} x + {reg.intercept_[0]}")
    predict_y = reg.predict(exp1_1_test_data)
    predict_result = [[exp1_1_test_data[i][0], predict_y[i][0]] for i in range(len(exp1_1_test_data))]
    print(f"预测结果为：\n{"\n".join(f"x = {i[0]:.4}, y = {i[1]:.4}" for i in predict_result)}")

    # plt.scatter(x=[i[0] for i in predict_result], y=[i[1] for i in predict_result])
    exp1_1_origin_data_x, exp1_1_origin_data_y = load_exp1_1_data()
    exp1_1_origin_data_y_pred = reg.predict(exp1_1_origin_data_x)
    from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score
    MSE = mean_squared_error(exp1_1_origin_data_y, exp1_1_origin_data_y_pred)
    MAE = mean_absolute_error(exp1_1_origin_data_y, exp1_1_origin_data_y_pred)
    R2 = r2_score(exp1_1_origin_data_y, exp1_1_origin_data_y_pred)
    print(f"误差分析如下：\nMSE = {MSE:.4}\nMAE = {MAE:.4}\nR2 = {R2:.4}")
    plt.scatter(
        [i[0] for i in exp1_1_origin_data_x],
        [i[0] for i in exp1_1_origin_data_y],
        color="blue"
    )
    plt.plot(
        [i[0] for i in predict_result],
        [i[1] for i in predict_result],
        color="red",
        label="regression"
    )

    plt.show()



if __name__ == '__main__':
    test_exp1_1()
