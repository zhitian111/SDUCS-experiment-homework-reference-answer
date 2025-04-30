#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void solve()
{
  size_t n;
  cin >> n;
  vector<size_t> nums(n);
  for (size_t i = 0; i < n; i++)
  {
    cin >> nums[i];
  }
  vector<size_t> dp(n);
  vector<size_t> prev;
  vector<size_t> prev_len;
  dp[0] = 1;
  prev.push_back(nums[0]);
  prev_len.push_back(1);
  for (size_t i = 1; i < n; i++)
  {
    size_t index;
    size_t max_len = 0;
    bool new_prev = true;
    for (size_t j = 0; j < prev.size(); j++)
    {
      if (nums[i] > prev[j])
      {
        new_prev = false;
        if (prev_len[j] + 1 > max_len)
        {
          max_len = prev_len[j] + 1;
          index = j;
        }
      }
    }
    if (new_prev)
    {
      prev.push_back(nums[i]);
      prev_len.push_back(1);
    }
    else
    {
      prev.push_back(nums[i]);
      prev_len.push_back(max_len);
      // prev[index] = nums[i];
      // prev_len[index] = max_len;
      dp[i] = max(dp[i], max_len);
    }
  }
  cout << dp[n - 1] << endl;
}

int main()
{
  solve();
  return 0;
}
