#include <bits/stdc++.h>
using namespace std;

inline bool check(size_t num)
{
    if (!(num % 7))
    {
        return true;
    }
    while (num > 0)
    {
        if (num % 10 == 7)
        {
            return true;
        }
        num /= 10;
    }
    return false;
}


void solve()
{
    size_t n, m;
    cin >> n >> m;
    size_t cnt[n];
    memset(cnt, 0, sizeof(cnt));
    size_t game = 1;
    size_t index = 0;
    while (game <= m)
    {
        if (check(game))
        {
            cnt[index]++;
        }
        game++;
        index++;
        index %= n;
    }
    for (auto i : cnt)
    {
        cout << i << " ";
    }
}

int main()
{
    solve();
    return 0;
}