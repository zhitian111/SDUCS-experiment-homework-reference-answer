#include<bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    int right = 0;
    int left = 0;
    cin >> n;
    int a[n];
    for (int i = 0;i < n;i++)
    {
        cin >> a[i];
        right += a[i];
    }
    int cnt = 0;
    for (int i = 0;i < n - 1;i++)
    {
        left += a[i];
        right -= a[i];
        if (left == right)
        {
            cnt++;
        }
    }
    cout << cnt << endl;
}

int main()
{
    solve();
    return 0;
}