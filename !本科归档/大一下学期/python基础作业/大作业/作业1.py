def check(string):
    for i in range(len(string)):
        if string.count(string[i])==1:
            return string[i]
    return ""
#函数测试
print(check("12345678912345678"))