
import numpy as np

# 维度
n=eval(input("Enter the number of dimension of data: "))
# 聚类个数
k=eval(input("Enter the number of clusters: "))
# 数据个数
c=eval(input("Enter the number of data: "))
data = []
# 阈值
thresold=eval(input("Enter the threshold value: "))
# 聚类集合
sets=[]
# 质心向量
mu=[]
# 异常值
wrong=[]
# 数据输入
print("Enter the data")
for i in range(0,c):
    temdata=[]
    for j in range(n):
        temdata.append(eval(input()))
    data.append(temdata)
# 欧氏距离(L2范数)计算
def euclidean_distance(x,y):
    sum=0
    for i in range(len(x)):
        sum+=(x[i]-y[i])**2
    return np.sqrt(sum)
# 初始化
def initialize():
    for i in range(k):
        mu.append(data[i])
# 质心向量重置
def heart():
    global data
    global sets
    global mu
    if sets==[]:
        return True
    temmu=[]
    for i in range(k):
        temlist = [0 for l in range(n)]
        for j in sets[i]:
            for l in range(n):
                temlist[l]=temlist[l]+j[l]
        for l in range(n):
            temlist[l]=temlist[l]/len(sets[i])
        temmu.append(temlist)
    if temmu==mu:
        return False
    mu=temmu
    return True
# 聚类
def kmeans():
    global sets
    global data
    global mu
    global wrong
    while heart():
        temset=[[] for _ in range(k)]
        for i in data:
            temdistance=[0 for _ in range(k)]
            for j in range(k):
                temdistance[j]=euclidean_distance(i,mu[j])
            if min(temdistance) >= thresold:
                wrong.append(i)
                data.remove(i)
            else:
                temset[temdistance.index(min(temdistance))].append(i)
        if temset != sets:
            sets=temset

# 开始执行
initialize()
kmeans()
for i in range(k):
    print("第",i+1,"类为")
    for j in sets[i]:
        print(j)

if wrong==[]:
    print("数据中无异常值")

for i in range(len(wrong)):
    print("第",i+1,"个异常值为")
    print(wrong[i])
