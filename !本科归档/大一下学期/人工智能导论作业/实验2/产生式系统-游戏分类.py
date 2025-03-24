def judge_repeat(value,list=[]):
    for i in range(0,len(list)):
        if(list[i]==value):
            return 1
        else:
            if(i!=len(list)-1):
                continue
            else:
                return 0


def judge_last(list):
    for i in list:
        if(i=='17'):
            for i in list:
                if(i=='13'):
                    for i in list:
                        if(i=='9'):
                            print("博弈类+腾讯出品+操作简单→金铲铲之战")
                            print("所识别的游戏为金铲铲之战")
                            return 0
                        if(i=='11'):
                            for i in list:
                                if(i=='12'):
                                    for i in list:
                                        if(i=='16'):
                                            print("博弈类+团队合作+腾讯出品+操作复杂+社交性强→王者荣耀")
                                            print("所识别的游戏为王者荣耀")
                                            return 0
        elif(i=='19'):
            for i in list:
                if(i=='2'):
                    for i in list:
                        if(i=='11'):
                            print("开放世界类+角色养成+操作复杂→塞尔达传说：旷野之息")
                            print("所识别的游戏为塞尔达传说：旷野之息")
                            return 0
                        elif(i=='1'):
                            for i in list:
                                if(i=='15'):
                                    print("开放世界类+二次元+角色养成+角色可爱→原神")
                                    print("所识别的游戏为原神")
                                    return 0
        elif(i=='20'):
            for i in list:
                if(i=='2'):
                    for i in list:
                        if(i=='11'):
                            print("塔防类+操作复杂+角色养成→王国保卫战")
                            print("所识别的游戏为王国保卫战")
                            return 0
                        if(i=='1'):
                            for i in list:
                                if(i=='9'):
                                    for i in list:
                                        if(i=='15'):
                                            print("塔防类+角色可爱+二次元+角色养成+操作简单→明日方舟")
                                            print("所识别的游戏为明日方舟")
                                            return 0
        elif(i=='18'):
            for i in list:
                if(i=='16'):
                    for i in list:
                        if(i=='15'):
                            for i in list:
                                if(i=='13'):
                                    print("派对类+腾讯出品+角色可爱+社交性强→元梦之星")
                                    print("所识别的游戏为元梦之星")
                                    return 0
                                if(i=='14'):
                                    print("派对类+网易出品+角色可爱+社交性强→蛋仔派对")
                                    print("所识别的游戏为蛋仔派对")
                                    return 0
        else:
            if (list.index(i) != len(list) - 1):
                continue
            else:
                print("\n根据所给条件无法判断为哪款游戏")


game_properties_list={"1":"二次元","2":"角色养成","3":"益智","4":"非线性","5":"pve","6":"pvp","7":"探索",
                        "8":"关卡制","9":"操作简单","10":"欢乐","11":"操作复杂","12":"团队合作",
                        "13":"腾讯出品","14":"网易出品","15":"角色可爱","16":"社交性强",
                        "17":"博弈类","18":"派对类","19":"开放世界类","20":"塔防类",
                        "21":"原神","22":"明日方舟","23":"王者荣耀","24":"王国保卫战",
                        "25":"塞尔达传说：旷野之息","26":"蛋仔派对","27":"元梦之星","28":"金铲铲之战"}
print('''输入对应条件前面的数字:
                                *******************************************************
                                *1.二次元 2.角色养成 3.益智 4.非线性 5.pve 6.pvp 7.探索     *
                                *8.关卡制 9.操作简单 10.欢乐 11.操作复杂 12.团队合作         *
                                *13.腾讯出品 14.网易出品 15.角色可爱 16.社交性强             *
                                *17.博弈类 18.派对类 19.开放世界类 20.塔防类                *       
                                *******************************************************
                                *******************当输入数字0时!程序结束******************
     ''')

list_real=[]
while(1):

    real_num=input("请输入：")
    list_real.append(real_num)
    if(real_num=='0'):
        break
print("\n")
print("前提条件为：")

for i in range(0,len(list_real)-1):
    print(game_properties_list[list_real[i]],end=" ")
print("\n")
print("推理过程如下：")


for i in list_real:
    if (i == '6'):
        for i in list_real:
            if (i == '3'):
                if (judge_repeat('17', list_real) == 0):
                    list_real.append('17')
                    print("pvp+益智→博弈类")
    elif (i == '10'):
        for i in list_real:
            if (i == '9'):
                for i in list_real:
                    if(i=='6'):
                        if(judge_repeat('18',list_real) ==0):
                            list_real.append('18')
                            print("欢乐+操作简单+pvp→派对类")
    elif (i == '7'):
        for i in list_real:
            if (i == '4'):
                for i in list_real:
                    if(i=='5'):
                        if(judge_repeat('19',list_real) ==0):
                            list_real.append('19')
                            print("探索+非线性+pve→开放世界类")
    elif (i == '8'):
        for i in list_real:
            if (i == '3'):
                for i in list_real:
                    if(i=='5'):
                        if(judge_repeat('20',list_real) ==0):
                            list_real.append('20')
                            print("关卡制+pve+益智→塔防类")
    else:
        if (i != len(list_real) - 1):
            continue
        else:
            break

judge_last(list_real)