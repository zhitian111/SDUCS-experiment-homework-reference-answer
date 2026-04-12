#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

static ll sum_min(const vector<ll> &A, ll t) {
    ll s = 0;
    for (ll x : A) s += min(x, t);
    return s;
}

static void phase2(vector<ll> &b, ll R) {
    int n = (int)b.size();
    while (R > 0) {
        ll M = *max_element(b.begin(), b.end());
        if (M == 0) break;
        ll mn = *min_element(b.begin(), b.end());
        if (M == mn) {
            ll q = R / n;
            ll r = R % n;
            for (ll &x : b) x -= q;
            for (int i = 0; i < r; i++) b[i]--;
            break;
        }
        vector<int> pos;
        pos.reserve(n);
        for (int i = 0; i < n; i++)
            if (b[i] == M) pos.push_back(i);
        int t = (int)pos.size();
        if (t >= 2) {
            if (R >= (ll)t) {
                for (int p : pos) b[p]--;
                R -= t;
            } else {
                for (ll i = 0; i < R; i++) b[pos[(int)i]]--;
                R = 0;
            }
        } else {
            int p = pos[0];
            ll M2 = 0;
            for (int i = 0; i < n; i++)
                if (i != p) M2 = max(M2, b[i]);
            ll d = min(R, b[p] - M2);
            b[p] -= d;
            R -= d;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        ll m, k;
        cin >> n >> m >> k;
        vector<ll> A(n);
        for (int i = 0; i < n; i++) cin >> A[i];
        ll fm = sum_min(A, m);
        vector<ll> b(n);
        if (fm < k) {
            for (int i = 0; i < n; i++) b[i] = max(0LL, A[i] - m);
            ll R = k - fm;
            phase2(b, R);
        } else {
            ll lo = 1, hi = m;
            while (lo < hi) {
                ll mid = (lo + hi) >> 1;
                if (sum_min(A, mid) >= k) hi = mid;
                else lo = mid + 1;
            }
            ll r = lo;
            ll fprev = sum_min(A, r - 1);
            for (int i = 0; i < n; i++) b[i] = max(0LL, A[i] - (r - 1));
            ll need = k - fprev;
            for (int i = 0; i < n && need > 0; i++) {
                if (b[i] > 0) {
                    b[i]--;
                    need--;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (i) cout << ' ';
            cout << b[i];
        }
        cout << '\n';
    }
    return 0;
}
