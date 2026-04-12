#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> par(n + 1, 0);
    vector<vector<int>> ch(n + 1);
    queue<int> q;
    q.push(1);
    par[1] = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (v == par[u]) continue;
            par[v] = u;
            ch[u].push_back(v);
            q.push(v);
        }
    }
    vector<int> post;
    vector<int> st;
    vector<int> idx(n + 1, 0);
    st.push_back(1);
    while (!st.empty()) {
        int u = st.back();
        if (idx[u] < (int)ch[u].size()) {
            st.push_back(ch[u][idx[u]++]);
        } else {
            post.push_back(u);
            st.pop_back();
        }
    }
    vector<int> dpr(n + 1), dpg(n + 1), dpb(n + 1);
    for (int u : post) {
        long long sumB = 0, sumG = 0;
        for (int v : ch[u]) {
            sumB += dpb[v];
            sumG += dpg[v];
        }
        int bestG = (int)sumB;
        int bestB = (int)sumG;
        for (int v : ch[u]) {
            int candG = dpr[v] + (int)sumB - dpb[v];
            if (candG > bestG) bestG = candG;
            int candB = dpr[v] + (int)sumG - dpg[v];
            if (candB > bestB) bestB = candB;
        }
        int sumRG = 0;
        for (int v : ch[u]) {
            int mx = dpg[v];
            if (dpb[v] > mx) mx = dpb[v];
            sumRG += mx;
        }
        dpr[u] = 1 + sumRG;
        dpg[u] = bestG;
        dpb[u] = bestB;
    }
    int ans = dpr[1];
    if (dpg[1] > ans) ans = dpg[1];
    if (dpb[1] > ans) ans = dpb[1];
    cout << ans << '\n';
    return 0;
}
