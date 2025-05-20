#include <iostream>
#include <vector>
#define debug(x) std::cout<<#x<<":\t"<<x;
using namespace std;

void solve()
{
  int n, v;
  cin >> n >> v;
  struct item
  {
    int value;
    int weight;
    int group;
  };
  item items[n];
  int group_num = 0;
  vector<vector<int>> group;
  for (int i = 0; i < n; i++)
  {
    cin >> items[i].weight >> items[i].value >> items[i].group;
    group_num = max(group_num, items[i].group);
  }
  group.resize(group_num + 1);
  for (int i = 0; i < n; i++)
  {
    group[items[i].group].push_back(i);
  }
  vector<int> dp(v + 1, 0);
  for (int i = 1; i <= group_num; i++)
  {
    for (int j = v; j >= 0; j--)
    {
      for (auto k : group[i])
      {
        auto tem_item = items[k];
        if (j - tem_item.weight >= 0)
        {
          dp[j] = max(dp[j], dp[j - tem_item.weight] + tem_item.value);
        }
      }
    }
  }
  cout << dp[v] << endl;
}

int main()
{
  solve();
  return 0;
}
