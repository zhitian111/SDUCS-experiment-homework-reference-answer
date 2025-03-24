import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import math

data = pd.read_csv('res.txt', sep=" ",header=None)

# Create Map

x=[math.log(x+1)*4 for x in data[3]]
y=[math.log(x+1)/3 for x in data[4]]
# c=[(max(0,x/10000),max(0,x/10000),1) for x in data[1]]
# print(np.min(data[1]))
s=data[1]/4

plt.scatter(x,y,s=s)
plt.show()

