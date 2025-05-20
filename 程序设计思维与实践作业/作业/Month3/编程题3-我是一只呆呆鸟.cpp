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
    size_t a, b, c;
    cin >> a >> b >> c;
    cout << ((b < a && c < a) ? "Bingo" : "gugugu...");
}
int main()
{
    solve();
    return 0;
}