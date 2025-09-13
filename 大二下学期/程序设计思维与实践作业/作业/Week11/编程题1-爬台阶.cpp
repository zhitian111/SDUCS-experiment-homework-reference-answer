#include <iostream>
#include <vector>
using namespace std;

const int mod = 998244353;

void solve()
{
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> dp(n + 1, 0);
  vector<int> sum(n + 1, 0);
  vector<bool> unsafe(n + 1, false);

  dp[0] = 1;
  sum[0] = dp[0];

  for (int i = 0; i < m; i++)
  {
    int x;
    cin >> x;
    unsafe[x] = true;
  }

  for (int i = 1; i <= n; i++)
  {
    if (unsafe[i])
    {
      dp[i] = 0;
    }
    else
    {
      if (i > k)
      {
        dp[i] = (sum[i - 1] - sum[i - k - 1] + mod) % mod;
      }
      else
      {
        dp[i] = sum[i - 1] % mod;
      }
    }
    sum[i] = (sum[i - 1] + dp[i]) % mod;
  }

  cout << dp[n] << endl;
}
int main()
{
  solve();
  return 0;
}
