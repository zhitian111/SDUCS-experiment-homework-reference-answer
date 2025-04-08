#include <bits/stdc++.h>
using namespace std;

void solve()
{
    size_t n;
    cin >> n;
    size_t a[n];
    size_t cnt = 0;
    size_t max_val = 0;
    size_t ans = 0;
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        max_val = max_val > a[i]? max_val : a[i];
    }
    for (size_t i = 0; i < n; i++)
    {
        if (a[i] == max_val)
        {
            cnt++;
        }
        else
        {
            ans = max(ans, cnt);
            cnt = 0;
        }
    }
    ans = max(ans, cnt);
    cout << max_val << " " << ans << endl;
}


int main()
{
    solve();
    return 0;
}