#include <iostream>
using namespace std;

void solve()
{
    int n;
    cin >> n;
    int user[2000] = {0};
    int x;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        user[x]++;
        cout << user[x] << " ";
    }
}

int main()
{
    solve();
    return 0;
}