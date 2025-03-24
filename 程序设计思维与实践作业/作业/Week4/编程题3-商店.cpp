#include <iostream>
#define debug(x) cout << #x << "=" << x << endl;

using namespace std;

void solve()
{
    int T;
    cin >> T;
    for (int timer = 1; timer <= T; timer++)
    {
        int n;
        cin >> n;
        size_t a[n];
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        size_t bonus = 0;
        size_t cnt = 0;
        size_t tem = a[0];

        for (size_t i = 1; i < n; i++)
        {
            if (tem > a[i])
            {
                tem = a[i];
            }
            if (tem < a[i])
            {
                size_t finder = i;
                while (finder < n - 1 && a[finder + 1]>=a[finder])
                {
                    finder++;
                }
                i = finder;
                cnt += 2;
                bonus += a[i] - tem;
                tem = a[i];

            }
        }
        cout << bonus << ' ' << cnt << endl;
    }
}

int main()
{
    solve();
    return 0;
}