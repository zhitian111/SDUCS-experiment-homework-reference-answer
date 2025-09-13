from collections import deque

def min_button_presses(N, A, B, k):
    if A == B:
        return 0
    visited = [False] * (N + 1)
    queue = deque()
    queue.append((A, 0))
    visited[A] = True
    while queue:
        current, steps = queue.popleft()
        next_floor = current + k[current - 1]
        if next_floor == B:
            return steps + 1
        if 1 <= next_floor <= N and not visited[next_floor]:
            visited[next_floor] = True
            queue.append((next_floor, steps + 1))
        next_floor = current - k[current - 1]
        if next_floor == B:
            return steps + 1
        if 1 <= next_floor <= N and not visited[next_floor]:
            visited[next_floor] = True
            queue.append((next_floor, steps + 1))
    return -1


while True:
    line = input().strip()
    if line == '0':
        break
    N, A, B = map(int, line.split())
    k = list(map(int, input().strip().split()))
    result = min_button_presses(N, A, B, k)
    print(result)

