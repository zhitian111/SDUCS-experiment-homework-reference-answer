from constraint import Problem, AllDifferentConstraint




# 定义变量和域
variables = range(8)  # 8个变量，分别对应8列
domains = range(8)  # 每个变量的域是0到7，表示行号
# 用这种方式定义默认每个皇后不在同一列

# 添加变量和域
problem = Problem()
problem.addVariables(variables, domains)

# 添加约束
problem.addConstraint(AllDifferentConstraint(), variables) # 让每个皇后不在同一行
for i in variables:
    for j in variables:
        if i < j:
             problem.addConstraint(lambda x, y, k=i, l=j: x != y and abs(x - y) != l - k, (i, j))  # 让每个皇后不在同一对角线

# 求解
solutions = problem.getSolutions()


cnt=0
# 输出结果
for solution in solutions:
    board = []
    for i in variables:
        row = ['*' if solution[i] == j else '.' for j in domains]
        board.append(''.join(row))
    print('\n'.join(board))
    print()
    cnt+=1
print("共搜索到",cnt,"个解")