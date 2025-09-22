import sklearn.model_selection
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score

import numpy as np

# 下载/加载数据集

iris = load_iris()

# 划分训练集和测试集

x_train, x_test, y_train, y_test = train_test_split(iris.data, iris.target, test_size=0.2, random_state=11)


def l1_distance(x1, x2):
    return np.sum(np.abs(x1 - x2))


# 实现KNN模型

class KNN(object):
    def __init__(self, n_neighbors=1, dist_func=l1_distance):
        self.n_neighbors = n_neighbors
        self.dist_func = dist_func
        self.x = None
        self.y = None
    def fit(self, x_train, y_train):
        self.x = x_train
        self.y = y_train
        pass

    def predict_one(self, x_test):
        if self.x is None or self.y is None:
            raise Exception("请先调用fit方法")

        distances = []

        for i in self.x:
            distances.append(self.dist_func(i,x_test))
        sorted_index = np.argsort(distances)
        # print(distances[sorted_index[:self.n_neighbors]])
        result = {}
        for i in range(self.n_neighbors):
            if self.y[sorted_index[i]] not in result:
                result[self.y[sorted_index[i]]] = 1
            else:
                result[self.y[sorted_index[i]]] += 1
        # print(np.array(distances)[sorted_index])
        # print(result)
        return max(result, key=result.get)

    def predict(self, x_test):
        y_pred = []
        for i in x_test:
            y_pred.append(self.predict_one(i))
        return y_pred

if __name__ == '__main__':
    # print(x_train)
    # print(x_test)
    # print(y_train)
    # print(y_test)

    # KNN_model.fit(x_train, y_train)
    # y_pred = KNN_model.predict(x_test[0])


    kf = sklearn.model_selection.KFold(n_splits=10, shuffle=True, random_state=35)
    k_range = range(1, 11)
    cv_scores = []
    for k in k_range:
        KNN_model = KNN(n_neighbors=k)
        print("K:", k)
        fold_scores = []
        for train_index, test_index in kf.split(x_train):
            x_train_fold, x_test_fold = x_train[train_index], x_train[test_index]
            y_train_fold, y_test_fold = y_train[train_index], y_train[test_index]
            print("训练集大小：", len(x_train_fold), "测试集大小：", len(x_test_fold))
            print("训练集标签：", y_train_fold)
            print("测试集标签：", y_test_fold)
            KNN_model.fit(x_train_fold, y_train_fold)
            y_pred = KNN_model.predict(x_test_fold)
            print("预测结果：", y_pred)
            fold_scores.append(accuracy_score(y_test_fold, y_pred))
        print(fold_scores)
        cv_scores.append(np.mean(fold_scores))
    print(cv_scores)
    best_k = np.argmax(cv_scores) + 1
    print("最佳k值:", best_k)
    best_model = KNN(n_neighbors=best_k)
    best_model.fit(x_train, y_train)
    y_pred = best_model.predict(x_test)
    print("测试集准确率:", accuracy_score(y_test, y_pred))