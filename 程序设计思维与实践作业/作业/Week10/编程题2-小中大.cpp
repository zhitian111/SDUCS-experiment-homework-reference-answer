#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

void solve()
{
  long long n;
  cin >> n;
  long long a[n];
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
  }
  sort(a, a + n);
  cout << a[n - 1] << " ";
  long long mid = n / 2;
  if (n % 2 == 0)
  {
    long long tem = a[mid - 1] + a[mid];
    if (tem % 2 == 0)
    {
      cout << tem / 2 << " ";
    }
    else
    {
      cout << tem / 2 << ".5 ";
    }
  }
  else
  {
    cout << a[mid] << " ";
  }
  cout << a[0] << endl;
}

int main()
{
  solve();
  return 0;
}
