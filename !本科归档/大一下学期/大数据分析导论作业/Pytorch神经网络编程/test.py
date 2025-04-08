list=eval(input())
list1=list
for i in list:
    if list.count(i)!=1:
        list1.remove(i)
        list=list1
print(list)