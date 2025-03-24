from kanren import run, eq, membero, var, conde

# 定义八皇后问题的约束条件
def queens_puzzle(n):
    # 定义变量和域
    variables = tuple(var() for _ in range(n))
    domain = tuple(range(n))

    # 添加约束条件
    constraints = []
    for i in range(n):
        for j in range(i+1, n):
            constraints.append(conde([neq_constraint(variables[i], variables[j])],
                                     [diag_constraint(variables[i], variables[j], i, j)]))

    # 返回满足约束条件的解
    return run(n, variables, membero, domain, *constraints)

# 定义不相等约束条件
def neq_constraint(x, y):
    return (x, y)

# 定义不同对角线约束条件
def diag_constraint(x, y, i, j):
    return (abs(x - y) != abs(i - j))

# 解决八皇后问题并打印结果
solutions = queens_puzzle(8)
for solution in solutions:
    print(solution)
    board = [['Q' if solution[i] == j else '.' for j in range(8)] for i in range(8)]
    for row in board:
        print(' '.join(row))
    print()