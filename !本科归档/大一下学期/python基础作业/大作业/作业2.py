def check(lst):
    num=0
    count=0
    for i in lst:
        if lst.count(i)>count:
            count=lst.count(i)
            num=i
    return num
#函数测试
print(check(eval("1,2,12,311,5,5,13,135,13,53,1,34,5,13,51,13,121,21,321,122,3,11")))