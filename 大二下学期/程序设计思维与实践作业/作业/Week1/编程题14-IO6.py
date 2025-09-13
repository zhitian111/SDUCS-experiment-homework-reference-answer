import sys

for line in sys.stdin:
    s = line.strip().split()
    ans = 0
    for i in range(1, len(s)):
        ans += int(s[i])
    print(ans)