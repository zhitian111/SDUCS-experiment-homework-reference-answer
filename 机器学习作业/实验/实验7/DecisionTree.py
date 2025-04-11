import csv
def load_data(filename):
    return csv.reader(open(filename, 'r'))

data_reader = load_data('f:/Homework/机器学习作业/实验/实验7/ex7Data/ex7Data.csv')

for row in data_reader:
    print(row)