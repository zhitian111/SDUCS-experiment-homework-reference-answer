#include <iostream>
#include <cmath>
using namespace std;

void solve()
{
    size_t n;
    cin >> n;
    long long cnt[n];
    for (size_t i = 0; i < n; i++)
    {
        cin >> cnt[i];
    }
    for (size_t i = 0; i < n; i++)
    {
        if (i == 0)
        {
            cout << (cnt[1] + cnt[i]) / 2 << " ";
        }
        else if (i == n - 1)
        {
            cout << (cnt[n - 1] + cnt[i - 1]) / 2 << " ";
        }
        else
        {
            cout << (cnt[i - 1] + cnt[i + 1] + cnt[i]) / 3 << " ";
        }
    }
}

int main()
{
    solve();
    return 0;
}