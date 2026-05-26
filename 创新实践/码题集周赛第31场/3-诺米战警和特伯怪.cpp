#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    long long surplus = 0;
    long long ans = 0;
    for (int i = n; i >= 1; --i) {
        long long total = surplus + a[i];
        long long need = static_cast<long long>(n - i + 1);
        long long x = min(a[i], total / need);
        ans += x;
        surplus = total - x * need;
    }
    cout << ans << '\n';
    return 0;
}
