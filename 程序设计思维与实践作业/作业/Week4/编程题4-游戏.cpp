#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

void solve()
{
    size_t n, k;
    cin >> n >> k;
    vector<size_t> arr;
    for (size_t i = 0; i < n; i++)
    {
        size_t x;
        cin >> x;
        arr.push_back(x);
    }
    sort(arr.begin(), arr.end());
    // size_t best = numeric_limits<size_t>::min();
    size_t cnt = 0;
    for (size_t i = 0; i < n - 1; i++)
    {
        if (arr[i + 1] - arr[i] <= k)
        {
            cnt++;
        }
        else
        {
            // best = max(best, cnt);
            // cnt = 0;
        }
    }
    // best = max(best, cnt);
    cout << cnt << endl;
}

int main()
{
    solve();
    return 0;
}