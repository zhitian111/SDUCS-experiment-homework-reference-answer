#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

inline long long popcount(long long x)
{
    long long res = 0;
    while (x)
    {
        res += x & 1;
        x >>= 1;
    }
    return res;
}

inline void print_by_bit(long long x, long long n = 32)
{
    // cout << "0b";
    for (long long i = 31; i >= 0; i--)
    {
        if (i < n)
        {
            cout << (((1 << 31) & x) ? '1' : '0');            
        }
        x <<= 1;
    }
    cout << endl;
}
void solve()
{
    long long n, k;
    cin >> n >> k;
    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(k + 1, vector<long long>(1 << n, 0)));
    for (long long i = 0; i < 1 << n; i++)
    {
        for (long long j = 0; j <= k; j++)
        {
            if (popcount(i) == j)
            {
                if (((i & (i << 1)) == 0) && ((i & (i >> 1)) == 0))
                {
                    dp[0][j][i] = 1;
                }
            }
        }
    }

    for (long long i = 1; i < n; i++)
    {
        for (long long j = 0; j <= k; j++)
        {
            for (long long s = 0; s < 1 << n; s++)
            {
                if (popcount(s) > j)
                {
                    continue;
                }
                if (((s & (s << 1)) == 0) && ((s & (s >> 1)) == 0))
                {
                    // cout << "s: " << s << endl;
                    for (long long t = 0; t < 1 << n; t++)
                    {
                        if (popcount(s) + popcount(t) > j)
                        {
                            continue;
                        }

                        // cout << "t: " << t << endl;
                        if (((t & (t << 1)) == 0) && ((t & (t >> 1)) == 0))
                        {
                            if (((s & t) == 0) && ((s & (t << 1)) == 0) && ((s & (t >> 1)) == 0))
                            {
                                // cout << "t : \n";
                                // print_by_bit(t, n);
                                // cout << "s : \n";
                                // print_by_bit(s, n);

                                dp[i][j][s] += dp[i - 1][j - popcount(s)][t];
                                // cout << "dp[" << i - 1 << "][" << j - popcount(s) << "][" << t << "]: " << dp[i - 1][j - popcount(s)][t] << endl;
                            }

                        }


                    }
                    // cout << endl;
                    // cout << "dp[" << i << "]" << "[" << j << "]" << "[" << s << "]: " << dp[i][j][s] << endl;
                    //             cout << endl;
                }
            }
        }
    }
    long long ans = 0;
    for (auto i : dp[n - 1][k])
    {
        ans += i;
        // cout << i << " ";
    }

    cout << ans << endl;
}
int main()
{
    solve();
    return 0;
}