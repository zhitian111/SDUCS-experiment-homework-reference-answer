#include <cstdio>
#include <map>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;

using u64 = unsigned long long;
using u128 = __uint128_t;

const long long MOD = 998244353;

u64 mul_mod(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}

u64 pow_mod(u64 a, u64 d, u64 mod) {
    u64 r = 1;
    while (d) {
        if (d & 1) r = mul_mod(r, a, mod);
        a = mul_mod(a, a, mod);
        d >>= 1;
    }
    return r;
}

bool is_prime(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % p == 0) return n == p;
    }
    if (n < 37 * 37) return true;
    u64 d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    auto check = [&](u64 a) {
        u64 x = pow_mod(a % n, d, n);
        if (x == 1 || x == n - 1) return true;
        for (u64 i = 1; i < s; i++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) return true;
        }
        return false;
    };
    for (u64 a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (!check(a)) return false;
    }
    return true;
}

u64 gcd_u64(u64 a, u64 b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

u64 pollard(u64 n) {
    if ((n & 1) == 0) return 2;
    while (true) {
        u64 c = uniform_int_distribution<u64>(1, n - 1)(rng);
        u64 x = uniform_int_distribution<u64>(0, n - 1)(rng);
        u64 y = x;
        u64 d = 1;
        while (d == 1) {
            x = (mul_mod(x, x, n) + c) % n;
            y = (mul_mod(y, y, n) + c) % n;
            y = (mul_mod(y, y, n) + c) % n;
            d = gcd_u64(x > y ? x - y : y - x, n);
        }
        if (d != n) return d;
    }
}

void factor(u64 n, map<u64, int>& mp) {
    if (n == 1) return;
    if (is_prime(n)) {
        mp[n]++;
        return;
    }
    u64 d = pollard(n);
    factor(d, mp);
    factor(n / d, mp);
}

long long mod_pow(long long a, long long e) {
    long long r = 1;
    a %= MOD;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

long long comb(u64 n, int k) {
    if (k == 0) return 1;
    long long num = 1;
    long long nm = (long long)(n % (u64)MOD);
    for (int i = 0; i < k; i++)
        num = num * ((nm - i + MOD) % MOD) % MOD;
    long long den = 1;
    for (int i = 2; i <= k; i++)
        den = den * i % MOD;
    return num * mod_pow(den, MOD - 2) % MOD;
}

int main() {
    u64 N, M;
    scanf("%llu%llu", &N, &M);

    map<u64, int> mp;
    u64 n = N;
    for (u64 p = 2; p * p <= n && p <= 1000000; ++p) {
        if (n % p == 0) {
            int cnt = 0;
            while (n % p == 0) {
                n /= p;
                ++cnt;
            }
            mp[p] = cnt;
        }
    }
    if (n > 1) factor(n, mp);

    long long ans = 1;
    for (auto& pr : mp) {
        int e = pr.second;
        ans = ans * comb((u64)e + M - 1, e) % MOD;
    }

    printf("%lld\n", ans);
    return 0;
}
