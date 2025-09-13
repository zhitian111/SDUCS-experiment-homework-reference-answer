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

typedef vector<vector<long long>> Matrix;

Matrix matrixMultiply(const Matrix& a, const Matrix& b, long long p)
{
    Matrix result(2, vector<long long>(2, 0));
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            for (int k = 0; k < 2; ++k)
            {
                result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % p;
            }
        }
    }
    return result;
}

Matrix matrixPower(Matrix base, long long n, long long p)
{
    Matrix result = { {1, 0}, {0, 1} };
    while (n > 0)
    {
        if (n % 2 == 1)
        {
            result = matrixMultiply(result, base, p);
        }
        base = matrixMultiply(base, base, p);
        n /= 2;
    }
    return result;
}

long long fibonacciMod(long long n, long long p)
{
    if (n == 0) return 0;
    Matrix base = {{1, 1}, {1, 0}};
    Matrix result = matrixPower(base, n - 1, p);
    return result[0][0];
}

void solve()
{
    long long T, n, p;
    cin >> T;
    for (int i = 1; i <= T; ++i)
    {
        cin >> n >> p;
        cout << fibonacciMod(n, p) << endl;
    }
}

int main()
{
    solve();
    return 0;
}