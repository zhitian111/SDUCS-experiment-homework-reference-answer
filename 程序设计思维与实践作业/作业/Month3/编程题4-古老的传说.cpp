#include <bits/stdc++.h>
using namespace std;
template<typename T> inline void __debug(T x, string name)
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
void solve()
{
    long long n, h, x;
    cin >> n >> h >> x;
    long long y[n];
    for (long long i = 0; i < n; i++)
    {
        cin >> y[i];
    }
    for (long long i = 0; i < n; i++)
    {
        long long cost = max(0LL, y[i] - x);
        if (cost >= h)
        {
            cout << "NO" << endl;
            cout << i << endl;
            return;
        }
        h -= cost;
        x = max(x, y[i]);        
    }
    if (h > 0)
    {
        cout << "YES" << endl;
        cout << h << endl;
    }
}
int main()
{
    solve();
    return 0;
}