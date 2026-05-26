#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x1, y1, z1, x2, y2, z2, k;
    cin >> x1 >> y1 >> z1;
    cin >> x2 >> y2 >> z2;
    cin >> k;
    int a = x1 - x2, b = y1 - y2, c = z1 - z2;
    long long best = LLONG_MAX;
    for (int da = -k; da <= k; ++da) {
        int u = abs(da);
        for (int db = -(k - u); db <= k - u; ++db) {
            int v = abs(db);
            int rem = k - u - v;
            int dc = max(-rem, min(rem, -c));
            long long na = a + da, nb = b + db, nc = c + dc;
            best = min(best, na * na + nb * nb + nc * nc);
        }
    }
    cout << best << '\n';
    return 0;
}
