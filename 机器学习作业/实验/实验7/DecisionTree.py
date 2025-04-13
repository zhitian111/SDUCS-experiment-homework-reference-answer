import csv
def load_data(filename):
    return csv.reader(open(filename, 'r'))

data_reader = load_data('f:/Homework/机器学习作业/实验/实验7/ex7Data/ex7Data.csv')

for row in data_reader:
    print(row)

# 数据集类
class DataSet:

    pass

# 信息熵计算
def information_entropy(dataset:DataSet):
    
    pass

# 信息增益计算
def information_gain(dataset:DataSet):
    
    pass

# 