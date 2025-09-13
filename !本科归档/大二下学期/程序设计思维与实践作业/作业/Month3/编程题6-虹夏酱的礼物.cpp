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
int dp[1000000];
void solve()
{
    size_t n;
    cin >> n;
    long long num[n];
    for (size_t i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    long long ans = 0;
    for (long long  i = n - 1; i >= 0; i--)
    {
        if (dp[num[i]] == 0)
        {
            ans++;
            dp[num[i]] += 1;
            continue;
        }
        else
        {
            break;
        }
    }
    cout << n -  ans << endl;
}
int main()
{
    solve();
    return 0;
}