import csv
def load_data(filename):
    return csv.reader(open(filename, 'r'))


# 数据集类
class DataSet:
    data_count : int
    feature_count : int
    features : list
    features_names : list
    features_table : list
    labels : list
    labels_names : list
    labels_table : list
    def __init__(self, data_set:csv.reader):
        self.features_table = []
        self.labels_table = []
        for row in data_set:
            self.features_table.append(row[:len(row) - 1])
            self.labels_table.append(row[-1])
        self.labels_names = self.labels_table[0]
        self.features_names = self.features_table[0]
        self.labels = [float(value) for value in self.labels_table[1:]]
        self.features = [[float(value) for value in row[1:]] for row in self.features_table[1:]]
        self.data_count = len(self.features) - 1
        self.feature_count = len(self.features[0])
    def shuffle(self):
        pass
    def min_max_normalize(self):
        min_values = [float('inf') for i in range(self.feature_count)]
        max_values = [float('-inf') for i in range(self.feature_count)]
        for i in range(self.data_count):
            for j in range(self.feature_count):
                if self.features[i][j] < min_values[j]:
                    min_values[j] = self.features[i][j]
                if self.features[i][j] > max_values[j]:
                    max_values[j] = self.features[i][j]
        for i in range(self.data_count):
            for j in range(self.feature_count):
                self.features[i][j] = (self.features[i][j] - min_values[j]) / (max_values[j] - min_values[j])
                self.features_table[i + 1][j] = str(self.features[i][j])
    
    def __repr__(self):
        return "DataSet(data_count={}, feature_count={}, features_names={}, labels_names={})".format(self.data_count, self.feature_count, self.features_names, self.labels_names) + "\n" + str(self.features) + "\n" + str(self.labels)
    

# 信息熵计算
def information_entropy(dataset:DataSet):
    
    pass

# 信息增益计算
def information_gain(dataset:DataSet):
    
    pass

class DecisionNode:
    feature_name : str
    threshold : float
    left_children : list
    right_children : list
    def __init__(self, feature_name:str, threshold:float, left_children:list, right_children:list):
        self.feature_name = feature_name
        self.threshold = threshold
        self.left_children = left_children
        self.right_children = right_children
    def __init__(self):
        self.feature_name = ""
        self.threshold = 0.0
        self.left_children = []
        self.right_children = []
class DecisionTree:
    dataset : DataSet
    root : DecisionNode
    def build_tree(self, dataset:DataSet) -> DecisionNode:
        pass
    def __init__(self, dataset:DataSet):
        self.dataset = dataset
        self.root = self.build_tree(dataset)
if __name__ == '__main__':
    data_reader = load_data('f:/Homework/机器学习作业/实验/实验7/ex7Data/ex7Data.csv')
    data_set = DataSet(data_reader)
    data_set.min_max_normalize()
    decision_tree = DecisionTree(data_set)
