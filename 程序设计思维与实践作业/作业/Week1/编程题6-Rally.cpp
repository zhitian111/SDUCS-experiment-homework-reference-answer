#include <iostream>
using namespace std;

int calculate()
{
    int n;
    cin >> n;
    int a[n];
    int avg = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        avg += a[i];
    }
    avg /= n;
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < n; i++)
    {
        sum1 += (a[i] - avg) * (a[i] - avg);
        sum2 += (a[i] - avg - 1) * (a[i] - avg - 1);
    }
    return sum1 < sum2? sum1 : sum2;
}

void solve()
{
    cout << calculate();
}

int main()
{
    solve();
    return 0;
}