#include <cstdio>
#include <vector>
using namespace std;

int main() {
    int n;
    long long k;
    scanf("%d%lld", &n, &k);
    vector<long long> a(n + 1);
    vector<long long> b(n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++)
        scanf("%lld", &b[i]);

    long long pool = 0;
    long long days = 0;
    int level = 0;

    while (level < n) {
        long long g = b[level] * k;
        if (pool >= a[level + 1]) {
            pool -= a[level + 1];
            level++;
            continue;
        }
        long long need = a[level + 1] - pool;
        long long t = (need + g - 1) / g;
        days += t;
        pool += t * g - a[level + 1];
        level++;
        while (level < n && pool >= a[level + 1]) {
            pool -= a[level + 1];
            level++;
        }
    }

    printf("%lld\n", days);
    return 0;
}
