
#状态空间
SLUDGE={"SD":0,"MD":1,"LD":2}
GREASE={"NG":0,"MG":1,"LG":2}
TIME={"VS":0,"S":1,"M":2,"L":3,"VL":4}
ANS={0:"VS洗涤时间很短",1:"S洗涤时间短",2:"M洗涤时间中等",3:"L洗涤时间长",4:"VL洗涤时间很长"}

#隶属度计算函数
#污泥
def Sludge(x):
    sludge=[0,0,0]
    if 0<=x<=50:
        sludge[0]=(50-x)/50
        sludge[1]=x/50
    elif 50<=x<=100:
        sludge[1]=(100-x)/50
        sludge[2]=(x-50)/50
    elif x>100 or x<0:
        print("输入错误")
    return sludge
#油脂
def Grease(x):
    grease=[0,0,0]
    if 0<=x<=50:
        grease[0]=(50-x)/50
        grease[1]=x/50
    elif 50<=x<=100:
        grease[1]=(100-x)/50
        grease[2]=(x-50)/50
    elif x>100 or x<0:
        print("输入错误")
    return grease
#时间计算函数
def Time(x):
    sum1=0
    for i in x:
        sum1=sum1+i
    sum2=0
    for i in range(0,len(x)):
        sum2=sum2+i*20*x[i]
    return sum2/sum1
#模糊推理函数
def Rule(sludge,grease):
    time=[0,0,0,0,0]
    if sludge[SLUDGE["SD"]]!=0 and grease[GREASE["NG"]]!=0:
        time[TIME["VS"]]=min(sludge[SLUDGE["SD"]],grease[GREASE["NG"]])
    if sludge[SLUDGE["SD"]]!=0 and grease[GREASE["MG"]]!=0:
        time[TIME["M"]]=min(sludge[SLUDGE["SD"]],grease[GREASE["MG"]])
    if sludge[SLUDGE["SD"]]!=0 and grease[GREASE["LG"]]!=0:
        time[TIME["L"]]=min(sludge[SLUDGE["SD"]],grease[GREASE["LG"]])
    if sludge[SLUDGE["MD"]]!=0 and grease[GREASE["NG"]]!=0:
        time[TIME["S"]]=min(sludge[SLUDGE["MD"]],grease[GREASE["NG"]])
    if sludge[SLUDGE["MD"]]!=0 and grease[GREASE["MG"]]!=0:
        time[TIME["M"]]=min(sludge[SLUDGE["MD"]],grease[GREASE["MG"]])
    if sludge[SLUDGE["MD"]]!=0 and grease[GREASE["LG"]]!=0:
        time[TIME["L"]]=min(sludge[SLUDGE["MD"]],grease[GREASE["LG"]])
    if sludge[SLUDGE["LD"]]!=0 and grease[GREASE["NG"]]!=0:
        time[TIME["M"]]=min(sludge[SLUDGE["LD"]],grease[GREASE["NG"]])
    if sludge[SLUDGE["LD"]]!=0 and grease[GREASE["MG"]]!=0:
        time[TIME["L"]]=min(sludge[SLUDGE["LD"]],grease[GREASE["MG"]])
    if sludge[SLUDGE["LD"]]!=0 and grease[GREASE["LG"]]!=0:
        time[TIME["VL"]]=min(sludge[SLUDGE["LD"]],grease[GREASE["LG"]])
    return time

sludge=Sludge(int(input("输入污泥值：")))
grease=Grease(int(input("输入油脂值：")))
time=Rule(sludge,grease)
print("推理结果为：",time)
for i in range(0,len(time)):
    if time[i]==max(time):
        print("按照最大值法决策为：",ANS[i])
ans=Time(time)
print("预计洗涤时间为：",round(ans*(100/80),0))
