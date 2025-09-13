#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void solve()
{
  long long n;
  cin >> n;
  vector<long long> nums(1e7 + 10, 0);
  vector<long long> dp(1e7 + 10, 0);
  long long max_num = 0;
  for (long long i = 0; i < n; i++)
  {
    long long num;
    cin >> num;
    nums[num] += num;
    max_num = max(max_num, num);
  }
  dp[1] = nums[1];
  for (long long i = 2; i <= max_num; i++)
  {
    dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
  }
  cout << dp[max_num] << endl;
}
int main()
{
  solve();
  return 0;
}
