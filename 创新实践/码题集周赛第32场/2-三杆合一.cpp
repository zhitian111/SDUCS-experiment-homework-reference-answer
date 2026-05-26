#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a, b, f2, need;
    cin >> a >> b >> f2 >> need;
    const double pi = acos(-1.0);
    double ra = a * pi / 180.0, rb = b * pi / 180.0;
    double ans;
    if (need <= f2)
        ans = (double)need;
    else {
        double s = sin(ra + rb);
        ans = (double)f2 + (double)(need - f2) * (sin(ra) + sin(rb)) / s;
    }
    cout << fixed << setprecision(2) << ans << '\n';
    return 0;
}
