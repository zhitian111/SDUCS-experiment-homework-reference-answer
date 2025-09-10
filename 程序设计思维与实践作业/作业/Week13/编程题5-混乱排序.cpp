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
    size_t n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    vector<vector<long long>> dp(n, vector<long long>(1 << n, 0));
    for (size_t i = 0; i < n; i++)
    {
        dp[i][1 << i] = 1;
    }

    for (size_t s = 0; s < (1ULL << n); s++)
    {
        for (size_t i = 0; i < n; i++)
        {
            if (!(s & (1 << i)))
            {
                continue;
            }
            for (size_t j = 0; j < n; j++)
            {
                if (s & (1 << j))
                {
                    continue;
                }
                if (abs(a[i] - a[j]) > k)
                {
                    dp[j][s | (1 << j)] += dp[i][s];
                }
            }
        }
    }
    long long ans = 0;
    long long all = 1;
    for (size_t i = 1; i < n; i++)
    {
        all <<= 1;
        all |= 1;
    }

    for (size_t i = 0;i < n; i++)
    {
        ans += dp[i][all];
    }


    cout << ans << endl;
}
int main()
{
    solve();
    return 0;
}