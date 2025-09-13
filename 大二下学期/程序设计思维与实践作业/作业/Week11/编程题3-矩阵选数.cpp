#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

void solve()
{
  vector<vector<long long>> arr;
  long long n;
  cin >> n;
  arr.resize(3);
  arr[0].resize(n);
  arr[1].resize(n);
  arr[2].resize(n);
  for (long long i = 0; i < n; i++)
  {
    cin >> arr[0][i];
  }
  for (long long i = 0; i < n; i++)
  {
    cin >> arr[1][i];
  }
  for (long long i = 0; i < n; i++)
  {
    cin >> arr[2][i];
  }
  vector<vector<long long>> dp;
  long long INF = numeric_limits<int>::max();
  dp.resize(n + 1, vector<long long>(3, INF));
  dp[0][0] = 0;
  dp[0][1] = 0;
  dp[0][2] = 0;
  dp[1][0] = 0;
  dp[1][1] = 0;
  dp[1][2] = 0;
  for (long long i = 1; i < n; i++)
  {
    for (long long j = 0; j < 3; j++)
    {
      // cout << "arr[" << j << "][" << i << "] = " << arr[j][i] << endl;
      dp[i][j] = min(min(dp[i - 1][0] + abs(arr[j][i] - arr[0][i - 1]),
                         dp[i - 1][1] + abs(arr[j][i] - arr[1][i - 1])),
                     dp[i - 1][2] + abs(arr[j][i] - arr[2][i - 1]));
      // cout << "abs(arr[" << j << "][" << i
      //      << "] - arr[0][i - 1]) = " << abs(arr[j][i] - arr[0][i - 1]) <<
      //      endl;
      // cout << "abs(arr[" << j << "][" << i
      //      << "] - arr[1][i - 1]) = " << abs(arr[j][i] - arr[1][i - 1]) <<
      //      endl;
      // cout << "abs(arr[" << j << "][" << i
      //      << "] - arr[2][i - 1]) = " << abs(arr[j][i] - arr[2][i - 1]) <<
      //      endl;
    }
  }
  // cout << endl;
  // for (long long i = 0; i < 3; i++)
  // {
  //   for (long long j = 0; j <= n; j++)
  //   {
  //     cout << dp[j][i] << " ";
  //   }
  //   cout << endl;
  // }
  cout << min(min(dp[n - 1][0], dp[n - 1][1]), dp[n - 1][2]) << endl;
}
int main()
{
  solve();
  return 0;
}
