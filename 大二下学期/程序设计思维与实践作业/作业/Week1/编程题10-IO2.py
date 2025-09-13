while True:
    s = input()
    s = s.split()
    a = int(s[0])
    b = int(s[1])
    if a == 0 and b == 0:
        break
    print(a+b)