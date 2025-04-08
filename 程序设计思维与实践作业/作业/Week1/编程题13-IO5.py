n = int(input())

for i in range(n):
    s = input().split()
    # if s[0] == '0':
    #     break
    ans = 0
    for i in range(1, len(s)):
        ans += int(s[i])
    print(ans)
