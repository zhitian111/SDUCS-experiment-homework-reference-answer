import numpy as np
污泥 = [0,0.5,1]
油脂 = [0,0.5,1]
time = [0,0.25,0.5,0.75,1]
#污泥and油脂
污泥和油脂 = np.zeros((len(污泥),len(油脂)))
for i in range(len(污泥)):
    for j in range(len(油脂)):
        污泥和油脂[i,j] = max(污泥[i],油脂[j])
污泥和油脂 = 污泥和油脂.reshape(9,1)
R = np.zeros((len(污泥和油脂),len(time)))
for i in range(len(污泥和油脂)):
    for j in range(len(time)):
        R[i][j] = min(min(污泥和油脂[i]),time[j])
x1= [0,0.83,0.6]
y1= [0,0.71,0.7]
x1y1=np.zeros((len(x1),len(y1)))
for i in range(len(x1)):
    for j in range(len(y1)):
        x1y1[i,j] = max(x1[i],y1[j])
x1y12 = x1y1.reshape(9)
result = np.zeros(5)
a = np.zeros(9)
for i in range(5):
    for j in range(9):
        a[j] = x1y12[j]*R[j,i]
    result[i] = max(a)

print(result)

        
