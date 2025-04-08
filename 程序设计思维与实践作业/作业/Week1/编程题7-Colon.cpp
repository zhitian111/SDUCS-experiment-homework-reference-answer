#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

void solve()
{
    int a, b, H, M;
    cin >> a >> b >> H >> M;
    double theta = (H * 30.0 + M / 2.0 - M * 6.0) / 360.0 * 2 * M_PI;
    // cout << theta;
    double c = sqrt(-(cos(theta) * 2.0 * a * b) + a * a + b * b);
    printf("%.20lf", c);
}

int main()
{
    solve();
    return 0;
}