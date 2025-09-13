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
  int dp[w + 1];
  for (int i = 0; i <= w; i++)
  {
    dp[i] = 0;
  }
  for (int i = 1; i <= w; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (i - items[j].weight >= 0)
      {
        dp[i] = max(dp[i], dp[i - items[j].weight] + items[j].value);
      }
      else
      {
        dp[i] = max(dp[i], dp[i - 1]);
      }
    }
  }
  cout << dp[w] << "\n";
}
int main()
{
  solve();
  return 0;
}
