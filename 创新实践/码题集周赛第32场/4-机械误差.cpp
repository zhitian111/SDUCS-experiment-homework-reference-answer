#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

using ll = long long;

ll n;
int m;
double a, b;

static const double DMIN = 0.021;

inline double fv(ll x) { return a * (double)x + b * sin((double)x); }

bool ok(double T) {
    int c = 0;
    ll i = 1;
    double lim = 2 * T;
    while (i <= n) {
        if (++c > m) return false;
        double base = fv(i);
        ll ans;
        if (fv(n) <= base + lim) {
            ans = n;
        } else {
            ll span = (ll)(lim / DMIN) + 64;
            ll hi = n;
            if (i + span < hi) hi = i + span;
            ll lo = i;
            ans = i;
            while (lo <= hi) {
                ll mid = (lo + hi) >> 1;
                if (fv(mid) <= base + lim) {
                    ans = mid;
                    lo = mid + 1;
                } else
                    hi = mid - 1;
            }
        }
        i = ans + 1;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> a >> b;
    if (m >= n) {
        cout.setf(ios::fixed);
        cout << setprecision(6) << 0.0 << "\n";
        return 0;
    }
    double lo = 0, hi = (fv(n) - fv(1)) / 2;
    for (int it = 0; it < 56; ++it) {
        double mid = (lo + hi) / 2;
        if (ok(mid))
            hi = mid;
        else
            lo = mid;
    }
    cout.setf(ios::fixed);
    cout << setprecision(6) << hi << "\n";
    return 0;
}
