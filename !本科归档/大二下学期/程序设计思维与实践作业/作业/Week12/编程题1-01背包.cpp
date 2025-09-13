#include <iostream>
using namespace std;

void solve()
{
  int n, w;
  cin >> n >> w;
  struct item
  {
    int weight;
    int value;
  };
  item items[n];
  for (int i = 0; i < n; i++)
  {
    cin >> items[i].weight >> items[i].value;
  }
  int dp[w + 1][n + 1];
  for (int i = 0; i <= n; i++)
  {
    dp[0][i] = 0;
  }
  for (int i = 1; i <= w; i++)
  {
    dp[i][0] = 0;
  }
  for (int i = 1; i <= w; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      if (i < items[j - 1].weight)
      {
        dp[i][j] = dp[i][j - 1];
      }
      else
      {
        dp[i][j] = max(dp[i][j - 1],
                       dp[i - items[j - 1].weight][j - 1] + items[j - 1].value);
      }
    }
  }
  cout << dp[w][n] << "\n";
}
int main()
{
  solve();
  return 0;
}
