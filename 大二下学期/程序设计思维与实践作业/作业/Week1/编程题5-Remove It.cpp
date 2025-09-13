#include <iostream>
using namespace std;
void solve()
{
    int n;
    cin >> n;
    int m;
    cin >> m;
    int a[n];
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        if (num != m)
        {
            a[j++] = num;
        }
        else
        {
            continue;
        }
    }
    for (int i = 0; i < j; i++)
    {
        cout << a[i] << " ";
    }
}

int main()
{
    solve();
    return 0;
}
