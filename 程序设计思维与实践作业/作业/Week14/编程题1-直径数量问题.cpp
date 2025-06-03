#include <bits/stdc++.h>
using namespace std;
template<typename T> inline void __debug__(T x, string name)
{
    cerr << name << " = " << x << endl;
}
template<typename T> inline void __debug__(T* x, string name, size_t size)
    {
    cerr << name << "[" << size << "] = ";
    for (size_t i = 0; i < size; i++)
    {
        cerr << x[i] << " ";
    }
    cerr << endl;
}
#define debug(x) __debug__(x, (#x));
#define adebug(x) __debug__(x, (#x), sizeof(x)/sizeof(x[0]));

int n;
typedef vector<vector<int>> graph;
graph adj;

vector<int> dp1;
vector<int> dp2;
vector<int> cnt;
vector<bool> vis;
int ans;
int ans_count;
    
void dfs(int s)
{
    for (auto i : adj[s])
    {
        if (vis[i]) continue;
        vis[i] = true;
        dfs(i);
        if (dp1[s] + dp1[i] + 1 > ans)
        {
            ans = dp1[s] + dp1[i] + 1;
            ans_count = dp2[i] * dp2[s];
        }
        else if (dp1[s] + dp1[i] + 1 == ans)
        {
            ans_count += dp2[i] * dp2[s];
            
        }
        if (dp1[i] + 1 > dp1[s])
        {
            dp1[s] = dp1[i] + 1;
            dp2[s] = dp2[i];
        }
        else if (dp1[i] + 1 == dp1[s])
        {
            dp2[s] += dp2[i];            
        }

    }
}
void solve()
{
    cin >> n;
    adj.resize(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    
    dp1.resize(n + 1, 0);
    dp2.resize(n + 1, 0);
    cnt.resize(n + 1, 0);
    vis.resize(n + 1, false);
    for (int i = 1; i <= n; i++)
    {
        dp2[i] = 1;
    }
    vis[1] = true;
    dfs(1);
    // for (auto x : dp1)
    // {
    //     cout << x << " ";
    // }
    // cout << endl;
    // for (auto x : dp2)
    // {
    //     cout << x << " ";
    // }
    // cout << endl;
    cout << ans << " " << ans_count << endl;
}
int main()
{
    solve();
    return 0;
}