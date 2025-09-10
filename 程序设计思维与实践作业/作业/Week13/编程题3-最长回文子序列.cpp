#include <bits/stdc++.h>
using namespace std;

void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    int dp[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = 0;
        }
        dp[i][i] = 1;
    }

    for (int len = 0; len < n; len++)
    {
        for (int i = 0;i < n - len;i++)
        {
            int j = i + len;

            if (j == i)
            {
                dp[i][j] = 1;
                continue;
            }
            if (s[i] == s[j])
            {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            }
            else
            {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    cout << dp[0][n - 1] << endl;
}
int main()
{
    solve();
    return 0;
}