# 使用print语句输出一个用"*"组成的5x5的正方形
#方法一
for i in range(5):
    for j in range(5):
        print('*',end='')
    print()
print()
#方法二
print("""*****
*****
*****
*****
*****""")
print()
#方法三
for i in range(5):
    print('*****')