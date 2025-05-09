#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;

// template <typename T> inline vector<T> binary_split(const T num)
// {
//   vector<T> res;
//   auto tem = num;
//   for (T i = 1; tem > 0; tem -= i, i *= 2)
//   {
//     res.push_back(min(tem, i));
//   }
//   return res;
// }

vector<int> binary_split(const int num)
{
  vector<int> res;
  auto tem = num;
  for (int i = 1; tem > 0; tem -= i, i *= 2)
  {
    res.push_back(min(tem, i));
  }
  return res;
}
void solve()
{
  size_t n, w;
  cin >> n >> w;
  struct item
  {
    int weight;
    int value;
    int count;
  };
  vector<item> items(n);
  for (int i = 0; i < n; i++)
  {
    cin >> items[i].weight >> items[i].value >> items[i].count;
  }
  vector<item> items_vec;
  for (auto i : items)
  {
    for (auto j : binary_split(i.count))
    {
      item it = {i.weight * j, i.value * j, 1};
      items_vec.push_back(it);
    }
  }
  int dp[w + 10][items_vec.size() + 10];
  for (int i = 0; i <= w; i++)
  {
    for (int j = 0; j <= items_vec.size(); j++)
    {
      dp[i][j] = 0;
    }
  }
  for (int i = 1; i <= w; i++)
  {
    for (int j = 1; j <= items_vec.size(); j++)
    {
      if (i >= items_vec[j - 1].weight)
      {
        dp[i][j] = max(dp[i][j - 1], dp[i - items_vec[j - 1].weight][j - 1] +
                                         items_vec[j - 1].value);
      }
      else
      {
        dp[i][j] = dp[i][j - 1];
      }
    }
  }
  cout << dp[w][items_vec.size()] << endl;
}
int main()
{
  solve();
  return 0;
}
