#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;


void solve()
{
    size_t cnt = 0;
    size_t l, r, k;
    cin >> l >> r >> k;
    size_t tem = 1;
    while (true)
    {
        if (tem >= l && tem <= r)
        {
            cnt++;
            cout << tem << ' ';
        }
        if (numeric_limits<size_t>::max() / k < tem) break;
        tem *= k;
        if (tem > r) break;
    }
    if (cnt == 0) cout << -1;
}

int main()
{
    solve();
    return 0;
}