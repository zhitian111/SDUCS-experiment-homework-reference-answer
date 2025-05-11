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

vector<long long> binary_split(const int num)
{
  vector<long long> res;
  long long tem = num;
  for (long long i = 1; tem > 0; i *= 2)
  {
    long long add = min(i, tem);
    res.push_back(add);
    tem -= add;
  }
  return res;
}
void solve()
{
  size_t n, w;
  cin >> n >> w;
  struct item
  {
    long long weight;
    long long value;
    long long count;
  };
  vector<item> items(n);
  for (long long i = 0; i < n; i++)
  {
    cin >> items[i].weight >> items[i].value >> items[i].count;
  }
  vector<item> items_vec;
  for (auto& i : items)
  {
    auto splits = binary_split(i.count);
    for (long long j : splits)
    {
      item it = {i.weight * j, i.value * j, 1};
      items_vec.push_back(it);
    }
  }
  vector<long long> dp(w + 1, 0);
  for (long long i = 1; i <= items_vec.size(); ++i)
  {
    auto weight = items_vec[i - 1].weight;
    auto value = items_vec[i - 1].value;
    for (long long j = w; j >= weight; --j)
    {
      dp[j] = max(dp[j], dp[j - weight] + value);
    }
  }
  cout << dp[w] << endl;
}
int main()
{
  solve();
  return 0;
}
