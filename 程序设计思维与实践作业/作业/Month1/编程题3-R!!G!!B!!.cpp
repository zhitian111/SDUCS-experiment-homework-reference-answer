#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

void solve()
{
    long long n;
    cin >> n;
    long long R, G, B;
    R = 0;
    G = 0;
    B = 0;
    // for (long long i = 0; i <= n; i++)
    // {
    //     char a;
    //     a = getchar();
    //     if (a == 'R')
    //     {
    //         R++;
    //     }
    //     if (a == 'G')
    //     {
    //         G++;
    //     }
    //     if (a == 'B')
    //     {
    //         B++;
    //     }
        
    //     // cout << a << endl;
    // }
    // cout << R << " " << G << " " << B << endl;
    string s;
    cin >> s;
    for (auto c : s)
    {
        if (c == 'R') R++;
        else if (c == 'G') G++;
        else if (c == 'B') B++;
    }
    cout << min({ R,G,B });
}

int main()
{
    solve();
    return 0;
}