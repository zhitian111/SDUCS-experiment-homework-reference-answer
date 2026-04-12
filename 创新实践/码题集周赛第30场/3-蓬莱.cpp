#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <array>
#include <functional>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    ll x;
    cin >> n >> m >> x;
    vector<ll> c(n + 1, 0);
    for (int i = 2; i <= n - 1; i++) cin >> c[i];
    vector<vector<pair<int, ll>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    const ll INF = (ll)4e18;
    vector<array<ll, 4>> dist(n + 1);
    for (int i = 1; i <= n; i++) dist[i].fill(INF);
    dist[1][0] = 0;
    dist[1][1] = 0;
    using Node = tuple<ll, int, int>;
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({0, 1, 0});
    pq.push({0, 1, 1});
    while (!pq.empty()) {
        auto [d, u, s] = pq.top();
        pq.pop();
        if (d != dist[u][s]) continue;
        if (u >= 2 && u <= n - 1) {
            if (s == 0) {
                ll nd = d + c[u];
                if (nd < dist[u][3]) {
                    dist[u][3] = nd;
                    pq.push({nd, u, 3});
                }
            } else if (s == 1) {
                ll nd = d + c[u];
                if (nd < dist[u][2]) {
                    dist[u][2] = nd;
                    pq.push({nd, u, 2});
                }
            }
        }
        for (auto [v, w] : adj[u]) {
            ll w1 = w - x;
            ll w2 = (w + 1) / 2;
            if (s == 0) {
                ll nd = d + w1;
                if (nd < dist[v][0]) {
                    dist[v][0] = nd;
                    pq.push({nd, v, 0});
                }
            } else if (s == 1) {
                ll nd = d + w2;
                if (nd < dist[v][1]) {
                    dist[v][1] = nd;
                    pq.push({nd, v, 1});
                }
            } else if (s == 2) {
                ll nd = d + w1;
                if (nd < dist[v][2]) {
                    dist[v][2] = nd;
                    pq.push({nd, v, 2});
                }
            } else {
                ll nd = d + w2;
                if (nd < dist[v][3]) {
                    dist[v][3] = nd;
                    pq.push({nd, v, 3});
                }
            }
        }
    }
    ll ans = dist[n][0];
    for (int s = 1; s < 4; s++) ans = min(ans, dist[n][s]);
    cout << ans << '\n';
    return 0;
}
