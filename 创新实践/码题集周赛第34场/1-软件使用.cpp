#include <cstdio>
#include <deque>
using namespace std;
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    deque<int> dq;
    for (int i = 0; i < n; i++) {
        int t;
        scanf("%d", &t);
        while (!dq.empty() && dq.front() < t - 3599)
            dq.pop_front();
        if ((int)dq.size() < k) {
            puts("Yes");
            dq.push_back(t);
        }
        else {
            puts("No");
        }
    }
    return 0;
}