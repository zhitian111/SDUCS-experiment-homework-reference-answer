#include <iostream>
#include <cmath>
using namespace std;


void solve()
{
    size_t n, x, y;
    cin >> n >> x >> y;
    size_t sum = 0;
    
    auto min_val = min(x, y);
    auto max_val = max(x, y);

    if (n == 0)
    {
        cout << 0 << endl;
        return;
    }
    if (n == 1)
    {
        cout << min_val << endl;
        return;
    }

    
    sum += min_val;

    double eta = (double)min_val / (min_val + max_val);
    double mu = (double)max_val / (min_val + max_val);
    // cout << mu << " " << eta << endl;
    double time_for_min = floor(double(n - 1) * mu) * min_val;
    double time_for_max = floor(double(n - 1) * eta) * max_val;

    // cout << time_for_min << " " << time_for_max << endl;

    sum += max(time_for_min, time_for_max);
    if (floor(double(n - 1) * mu) + floor(double(n - 1) * eta) == n - 1)
    {
        cout << sum << endl;
        return;
    }
    double minus = abs(time_for_min - time_for_max);
    if (time_for_max > time_for_min)
    {
        sum += min_val - minus;
    }
    else if (time_for_min > time_for_max)
    {
        sum += (double)max_val < min_val + minus ? max_val - minus : min_val;
    }
    else
    {
        sum += min_val;
    }
    cout << sum << endl;

}

int main()
{
    solve();
    return 0;
}