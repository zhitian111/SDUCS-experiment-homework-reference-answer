#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int m, n;
    cin >> m >> n;
    int a[m + 2][n + 2];
    for (int i = 0;i < m + 2;i++)
    {
        a[i][0] = numeric_limits<int>::min();
        a[i][n + 1] = numeric_limits<int>::min();
    }
    for (int i = 0;i < n + 2;i++)
    {
        a[0][i] = numeric_limits<int>::min();
        a[m + 1][i] = numeric_limits<int>::min();
    }
    // for (int i = 0;i < m + 2;i++)
    // {
    //     for (int j = 0;j < n + 2;j++)
    //     {
    //         cout << a[i][j] << "\t";
    //     }
    //     cout << endl;
    // }
    for (int i = 1;i <= m;i++)
    {
        for (int j = 1;j <= n;j++)
        {
            cin >> a[i][j];
        }
    }
    int cnt = 0;
    for (int i = 1;i <= m;i++)
    {
        for (int j = 1;j <= n;j++)
        {
            if (a[i][j] > a[i - 1][j] && a[i][j] > a[i + 1][j] && a[i][j] > a[i][j - 1] && a[i][j] > a[i][j + 1])
            {
                cnt++;
            }
        }
    }
    cout << cnt << endl;
}

int main()
{
    solve();
    return 0;
}

