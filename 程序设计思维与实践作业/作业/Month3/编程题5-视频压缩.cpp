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
struct pixel
{
    int r, g, b;
    bool operator==(const pixel& p) const
    {
        return r == p.r && g == p.g && b == p.b;
    }
    bool operator!=(const pixel& p) const
    {
        return r!= p.r || g!= p.g || b!= p.b;
    }
};
istream& operator>>(istream& is, pixel& p)
{
    is >> p.r >> p.g >> p.b;
    return is;
}
void solve()
{
    size_t h, w;
    cin >> h >> w;
    vector<vector<pixel>> img1(h, vector<pixel>(w));
    for (size_t i = 0; i < h; i++)
    {
        for (size_t j = 0; j < w; j++)
        {
            cin >> img1[i][j];
        }
    }
    vector<vector<pixel>> img2(h, vector<pixel>(w));
    for (size_t i = 0; i < h; i++)
    {
        for (size_t j = 0; j < w; j++)
        {
            cin >> img2[i][j];
        }
    }
    long long ans = 0;
    for (size_t i = 0; i < h; i++)
    {
        for (size_t j = 0; j < w; j++)
        {
            if (img1[i][j] != img2[i][j])
            {
                ans += 48;
            }
        }

    }
    long long size = 24 * h * w;
    cout << size - ans << endl;
}
int main()
{
    solve();
    return 0;
}