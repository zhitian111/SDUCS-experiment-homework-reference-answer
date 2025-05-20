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
void solve()
{
    int n;
    cin >> n;
    string s = "01";
    while (s.size() < n)
    {
        string s_inv = s;
        for (auto& c : s_inv)
        {
            c = c == '0' ? '1' : '0';
        }
        s = s + s_inv;
    }
    string target;
    cin >> target;
    int ans = 0;
    size_t start = s.find(target);
    while (start < string::npos)
    {
        ans++;
        start = s.find(target, start + 1);
    }
    cout << ans << endl;
}
int main()
{
    solve();
    return 0;
}