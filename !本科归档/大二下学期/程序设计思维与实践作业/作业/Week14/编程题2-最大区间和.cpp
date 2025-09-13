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
void solve()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    long long n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    long long ans = 0;
    // 滚动数组方案 tle
    // long long prefix = 0;
    // for (int len = 1; len <= m; len++)
    // {
    //     prefix += a[len - 1];
    //     long long tem = prefix;
    //     ans = ans > tem ? ans : tem;
    //     for (int i = 1; i + len - 1 < n; i++)
    //     {
    //         tem = tem - a[i - 1] + a[i + len - 1];
    //         ans = ans > tem ? ans : tem;
    //     }
    // }
    // mle
    // vector<vector<long long>> dp(m, vector<long long>(n, 0));
    // for (int i = 0; i < m; i++)
    // {
    //     tem += a[i];
    //     dp[i][0] = tem;
    //     ans = ans > tem? ans : tem;
    // }
    // for (int i = 1; i < n; i++)
    // {
    //     for (int j = 0; j < m && (j + i) < n; j++)
    //     {
    //         dp[j][i] = dp[j][i - 1] - a[i - 1] + a[j + i];
    //         ans = ans > dp[j][i]? ans : dp[j][i];
    //     }
    // }
    vector<long long> prefix_sum(n + 1, 0);
    for (int i = 0; i < n; i++)
    {
        prefix_sum[i + 1] = prefix_sum[i] + a[i];
    }

    deque<int> dq;
    dq.push_back(0);

    for (int i = 1; i <= n; i++)
    {
        while (!dq.empty() && dq.front() < i - m)
        {
            dq.pop_front();
        }
        ans = max(ans, prefix_sum[i] - prefix_sum[dq.front()]);
        while (!dq.empty() && prefix_sum[i] <= prefix_sum[dq.back()])
        {
            dq.pop_back();
        }
        dq.push_back(i);
    }

    cout << ans << endl;
}
int main()
{
    solve();
    return 0;
}