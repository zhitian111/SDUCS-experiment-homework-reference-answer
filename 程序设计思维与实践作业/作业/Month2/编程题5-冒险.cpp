#include <bits/stdc++.h>

using namespace std;

void solve()
{
    size_t n;
    cin >> n;
    size_t sum = 0;
    int x[n];
    for (size_t i = 0; i < n; i++)
    {
        cin >> x[i];
        sum += x[i];
    }
    size_t binary = sum / 2;
    size_t tem_sum = 0;
    size_t ans = ~0ULL;
    for (size_t i = 0; i < n; i++)
    {
        tem_sum += x[i];
        if (tem_sum > binary)
        {
            size_t m = tem_sum;
            ans = min((1 + m) * m + (1 + sum - m) * (sum - m), ans);
            m = tem_sum - x[i];
            ans = min((1 + m) * m + (1 + sum - m) * (sum - m), ans);
            break;
        }
    }
    cout << ans / 2 << endl;
}

int main()
{
    solve();
    return 0;
}