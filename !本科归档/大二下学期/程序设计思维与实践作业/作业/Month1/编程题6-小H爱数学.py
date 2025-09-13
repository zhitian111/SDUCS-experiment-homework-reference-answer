def solve():
    cnt = 0
    tem = 1
    l, r, k = map(int, input().split())
    
    while True:
        if tem >= l and tem <= r:
            cnt += 1
            print(tem, end=' ')
        tem *= k
        if tem > r:
            break
    
    if cnt == 0:
        print(-1)

solve()
