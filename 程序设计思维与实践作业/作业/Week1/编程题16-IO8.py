import sys

for line in sys.stdin:
    s = line.strip().split()
    ans = 0
    for i in range(0, len(s)):
        ans += int(s[i],16)
    print(int(ans))