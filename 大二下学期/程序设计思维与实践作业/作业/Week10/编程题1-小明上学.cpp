#include <iostream>

using namespace std;

void solve()
{
  int r, y, h;
  cin >> r >> y >> h;

  int n;
  cin >> n;
  int ans = 0;
  for (int i = 0; i < n; i++)
  {
    int k;
    int t;
    cin >> k >> t;
    if (k == 0)
    {
      ans += t;
    }
    if (k == 1)
    {
      ans += t;
    }
    if (k == 3)
    {
      ans += 0;
    }
    if (k == 2)
    {
      ans += t + r;
    }
  }
  cout << ans << endl;
}

int main()
{
  solve();
  return 0;
}
