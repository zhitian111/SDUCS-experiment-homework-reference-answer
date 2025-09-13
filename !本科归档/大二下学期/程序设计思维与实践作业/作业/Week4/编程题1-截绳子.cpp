#include <iostream>
#include <cmath>
using namespace std;

void solve()
{
    int n;
    int k;
    cin >> n;
    int arr[n];
    cin >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    double left = 0, right = 1 << 30;
    while (left + 1e-7 < right)
    {
        double mid = (left + right) / 2;
        double sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += floor(arr[i] / mid);
        }
        if (sum >= k)
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }
    cout << (left + right) / 2 << endl;
}

int main()
{
    solve();
    return 0;
}