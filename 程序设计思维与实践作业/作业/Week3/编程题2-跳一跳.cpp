#include <iostream>

using namespace std;

void solve()
{
    int count = 1;
    int sum = 0;
    int a;
    while (true)
    {
        cin >> a;
        if (a == 0)
        {
            break;
        }
        if (a == 1)
        {
            sum++;
            count = 1;
        }
        if (a == 2)
        {
            sum += 2 * count;
            count++;
        }
    }
    cout << sum << endl;
}

int main()
{
    solve();
    return 0;
}