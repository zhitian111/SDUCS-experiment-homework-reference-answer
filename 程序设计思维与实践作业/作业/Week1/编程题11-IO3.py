import sys

for line in sys.stdin:
    s = line.strip().split()
    if not s:
        break
    a = int(s[0])
    b = int(s[1])
    print(a + b)
