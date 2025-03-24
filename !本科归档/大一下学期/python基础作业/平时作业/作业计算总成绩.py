# 编写一个函数 calculate_total_score() ，该函数接受一个包
# 含学生姓名和对应成绩的字典作为参数。字典中的键是学生
# 姓名，值是他们的成绩（整数）。函数需要计算并返回所有
# 学生的总成绩之和。
# 学生和成绩如下：
# Alice: 85
# Bob: 92
# Charlie: 88
# David: 78

score={"Alice":85,"Bob":92,"Charlie":88,"David":78}

def calculate_total_score(dictionary):
    sum=0
    for key in dictionary:
        sum+=dictionary[key]
    return sum
print(calculate_total_score(score))