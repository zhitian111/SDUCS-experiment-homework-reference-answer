#include <bits/stdc++.h>
using namespace std;
template<typename T> inline void __debug__(T x, string name)
{
    cerr << name << " = " << x << endl;
}
template<typename T> inline void __debug__(T* x, string name, size_t size)
    {
    cerr << name << "[" << size << "] = ";
    for (size_t i = 0; i < size; i++)
    {
        cerr << x[i] << " ";
    }
    cerr << endl;
}
#define debug(x) __debug__(x, (#x));
#define adebug(x) __debug__(x, (#x), sizeof(x)/sizeof(x[0]));
long long mod = 998244353;
const int N = 3;
class Matrix
{
public:
    
    long long x[N][N];
    Matrix()
    {
        memset(x, 0, sizeof(x));
    }
    Matrix(const Matrix& b)
    {
        memcpy(x, b.x, sizeof(x));
    }
    Matrix operator*(const Matrix& b) const
    {
        Matrix c;
        for (long long i = 0; i < N; i++)
            for (long long j = 0; j < N; j++)
            {
                c.x[i][j] = 0;
                for (long long k = 0; k < N; k++)
                {
                    c.x[i][j] += x[i][k] * b.x[k][j] % mod;
                    c.x[i][j] %= mod;
                }
            }
        return c;
    }
    Matrix pow(long long n) const
    {
        Matrix res;
        for (long long i = 0; i < N; i++)
        {
            res.x[i][i] = 1;        
        }
        Matrix a = *this;
        while (n)
        {
            if (n & 1) res = res * a;
            a = a * a;
            n >>= 1;
        }
        return res;
    }
};

inline void solve()
{
    int n;
    cin >> n;
    Matrix a, b;
    // 1 0 1
    // 0 1 1
    // 2 2 1
    a.x[0][0] = 1;
    a.x[0][2] = 1;
    a.x[1][1] = 1;
    a.x[1][2] = 1;
    a.x[2][0] = 2;
    a.x[2][1] = 2;
    a.x[2][2] = 1;
    for (int i = 0; i < n; i++)
    {
        size_t m;
        cin >> m;
        b = a.pow(m - 1);
        cout << (b.x[0][0] % mod + ((b.x[0][2] % mod) * 2) % mod) % mod << endl;
    }
}
int main()
{
    solve();
    return 0;
}