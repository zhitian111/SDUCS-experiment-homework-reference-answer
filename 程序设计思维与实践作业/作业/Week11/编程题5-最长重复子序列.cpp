#include <bits/stdc++.h>
using namespace std;

void solve()
{
    size_t n1, n2;
    cin >> n1 >> n2;
    vector<size_t> A(n1 + 1), B(n2 + 1);
    for (size_t i = 1; i <= n1; i++)
    {
        cin >> A[i];        
    }
    for (size_t i = 1; i <= n2; i++)
    {
        cin >> B[i];
    }

    vector<vector<size_t>> dp(n1 + 1, vector<size_t>(n2 + 1, 0));
    for (size_t i = 1; i <= n1; i++)
    {
        for (size_t j = 1; j <= n2; j++)
        {
            dp[i][j] = max(max(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1] + (A[i] == B[j] ? 1 : 0));    
        }
    }
    cout << dp[n1][n2] << endl;
}
int main()
{
    solve();
    return 0;
}