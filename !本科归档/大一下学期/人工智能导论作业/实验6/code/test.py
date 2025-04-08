import networkx as nx
import pandas as pd
import copy
import random
import time

df = pd.read_excel(r'C:\Users\23676\Downloads\附件1(Attachment 1)-交通需求(交通网络2)Traffic demand (Network 2).xlsx')
#创建有向图
G = nx.DiGraph()

edges=[(1,2),(1,3),(2,1),(2,3),(2,4),(2,5),(3,1),(3,2),(3,5),(3,6),(4,2),(4,5),(4,7),(5,2),(5,3),(5,4),(5,6),(5,7),(5,8),(6,3),(6,5),(6,8),(6,9),(7,4),(7,5),(7,8),(8,5),(8,6),(8,7),(8,9),(9,6),(9,8)]
G.add_edges_from(edges,flow=0)
def allocate_demands(G,demands):
    D=[]
    C=[]
    for index,row in demands.iterrows():
        origin,destination,demand = row['起点 (origin)'],row['终点 (destination)'],row['需求量 (demand)']

#使用bijkstra 算法找到所有最短路径
        all_paths = list(nx.all_shortest_paths(G, source=origin,target=destination))

        path_flow =demand /len(all_paths)
        #for i in range(len(D)):

          #  D[i]=[/]*len(D[i])

        for path in all_paths:
            for i in range(len(path) - 1):
                G[path[i]][path[i + 1]]['flow'] += path_flow
        D.append([path_flow]*len(all_paths))
        C.append(all_paths)

    return D,C

edges_list=['%s, %s'%(i, j) for i,j in edges]


print(edges_list)


Flow,Paths=allocate_demands(G,df)
#Flow为原始的车流量矩阵
#Paths为原始的路径矩阵
print('路径',Paths)
print('流量',Flow)
def objective(Paths,Flow,edges_list):
    liuliangji=[]
    temsum=0
    for x in edges_list:#遍历路径，并判断方案是否损坏，若损坏，则会添加到删除矩阵
        #print(x,"损坏")
        flow=Flow.copy()
        paths = copy.deepcopy(Paths)
        liuliang=0
        sunhuaifangan=[]
        mark = 1
        for i in range(len(Paths)):
            for j in range(len(Paths[i])):
                paths[i][j]=str(paths[i][j])
                # if x == edges_list[0]:
                #     print('paths',paths[i][j])
                if x in paths[i][j]:
                    if mark == 1:
                        print('x', x)
                        mark=0

                    sunhuaifangan.append([i,j])
                    liuliang+=Flow[i][j]
                    # print("liuliang加了",Flow[i][j])
        temsum += liuliang
        # print("temsum",temsum)
        liuliangji.append(liuliang)
    # print(liuliangji)
    # print(sum(liuliangji))
    return sum(liuliangji)

Iteration_number=1#迭代次数
Flown=copy.deepcopy(Flow)
random.seed(time.time())
def tuihuo(paths,Flown,Flow):

    for i in range(len(Flown)):
        sump=0
        if len(Flown[i])==1:
            continue
        for j in range(len(Flown[i])-1):
            # if i == 0:
            #     print('sum',sum(Flown[i]))
            Flown[i][j] = min(random.uniform(Flown[i][j]*0.6, Flown[i][j]*1.4),sum(Flown[i]),max(sum(Flown[i])-sump,0))
            # 生成A的90%的值
            sump+=Flown[i][j]
        Flown[i][-1]=max(sum(Flow[i])-sump,0)
    # print(Flown)
    return Flown


A=50000
for i in range(Iteration_number):
    # print("object是",objective(Paths, Flown, edges_list))
    temflow=Flown
    Flown = tuihuo(Paths, Flown, Flow)
    B=objective(Paths, Flown, edges_list)
    if B<A:
        A=B
    else:
        Flown=temflow
    print(A)
    # print(Flown)
#x=[str(i) for i in edges]
#print(x)

#pos = nx.spring_layout(G)

#edge_labels ={(u, v):f'{d["flow"]:.0f}'for u,v, d in G.edges(data=True)}
#nx.draw(G, pos, with_labels=True, node_color='skyblue',node_size=2000,edge_color='k',linewidths=1, font_size=15)
#nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
#plt.show()