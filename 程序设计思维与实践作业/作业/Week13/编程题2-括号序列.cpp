#include <bits/stdc++.h>
using namespace std;

string s;
int f[1000][1000];
int n;
    const int inf = 1e9;
void recurve(int i,int j)
{
    for (int k = i; k < j; k++)
    {
        if (f[i][k] == inf)
        {
            recurve(i, k);            
        }
        if (f[k + 1][j] == inf)
        {
            recurve(k + 1, j);
        }
        f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
    }
    if ((s[i] == '(' && s[j] == ')') || (s[i] == '[' && s[j] == ']'))
    {
        f[i][j] = min(f[i][j], f[i + 1][j - 1]);
    }
    else if ((s[i] == '(' && s[j] != ')') || (s[i] == '[' && s[j] != ']'))
    {
        f[i][j] = min(f[i][j], f[i + 1][j] + 1);
    }
    else if ((s[i] != '(' && s[j] == ')') || (s[i] != '[' && s[j] == ']'))
    {
        f[i][j] = min(f[i][j], f[i][j - 1] + 1);
    }    

}

void solve()
{
    cin >> s;
    n = s.size();
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            f[i][j] = inf;
        }
    }
    for (int i = 0; i <= n; i++)
    {
        f[i][i] = 1;
        if (s[i] == '(' && s[i + 1] == ')')
        {
            f[i][i + 1] = 0;
        }
        if (s[i] == '[' && s[i + 1] == ']')
        {
            f[i][i + 1] = 0;
        }
    }
    recurve(0, n - 1);    
    cout << f[0][n - 1] << endl;
}
int main()
{
    solve();
    return 0;
}