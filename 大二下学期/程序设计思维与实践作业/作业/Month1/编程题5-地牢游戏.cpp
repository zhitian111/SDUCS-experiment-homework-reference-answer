#include <iostream>
#include <algorithm>
using namespace std;

void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        int sum = a + b + c;
        if (sum % 9 != 0)
        {
            cout << "NO" << endl;
            continue;
        }
        int x = sum / 9;
        if (min({ a,b,c }) < x)
        {
            cout << "NO" << endl;
            continue;
        }
        cout << "YES" << endl;
    }
}

int main()
{
    solve();
    return 0;
}