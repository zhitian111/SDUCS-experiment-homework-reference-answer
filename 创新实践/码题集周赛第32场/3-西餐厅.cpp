#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const ll INF = (ll)4e18;

int w2[3], w3[3];

inline int enc(int d, int len) { return 1 + d * 3 + (len - 1); }

inline void dec(int s, int &last, int &len) {
    if (s == 0) {
        last = -1;
        len = 0;
        return;
    }
    int t = s - 1;
    last = t / 3;
    len = t % 3 + 1;
}

inline int stepCost(int p, int s, int drink) {
    if (s == 0) return 0;
    int last, len;
    dec(s, last, len);
    if (drink != last) return 0;
    int nl = min(len + 1, 3);
    if (nl == 2) return w2[p];
    return w3[p];
}

inline int stepState(int s, int drink) {
    if (s == 0) return enc(drink, 1);
    int last, len;
    dec(s, last, len);
    if (drink != last) return enc(drink, 1);
    return enc(drink, min(len + 1, 3));
}

inline int sid(int sa, int sb, int sc) { return sa * 100 + sb * 10 + sc; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n >> w2[0] >> w3[0] >> w2[1] >> w3[1] >> w2[2] >> w3[2];
    vector<array<int, 3>> inv(n);
    for (int i = 0; i < n; i++) cin >> inv[i][0] >> inv[i][1] >> inv[i][2];

    vector<ll> dp(1000, INF), ndp(1000, INF);
    dp[sid(0, 0, 0)] = 0;

    for (int day = 0; day < n; day++) {
        fill(ndp.begin(), ndp.end(), INF);
        int A = inv[day][0], B = inv[day][1], C = inv[day][2];
        for (int id = 0; id < 1000; id++) {
            ll base = dp[id];
            if (base >= INF) continue;
            int sc = id % 10;
            int sb = (id / 10) % 10;
            int sa = id / 100;
            for (int x = 0; x < 3; x++)
                for (int y = 0; y < 3; y++)
                    for (int z = 0; z < 3; z++) {
                        int c0 = (x == 0) + (y == 0) + (z == 0);
                        int c1 = (x == 1) + (y == 1) + (z == 1);
                        int c2 = (x == 2) + (y == 2) + (z == 2);
                        if (c0 > A || c1 > B || c2 > C) continue;
                        int nsa = stepState(sa, x);
                        int nsb = stepState(sb, y);
                        int nsc = stepState(sc, z);
                        ll add = (ll)stepCost(0, sa, x) + stepCost(1, sb, y) + stepCost(2, sc, z);
                        int nid = sid(nsa, nsb, nsc);
                        ll v = base + add;
                        if (v < ndp[nid]) ndp[nid] = v;
                    }
        }
        dp.swap(ndp);
    }
    ll ans = INF;
    for (ll v : dp) ans = min(ans, v);
    cout << ans << "\n";
    return 0;
}
