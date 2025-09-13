#include<iostream>
#include<string>
using namespace std;
bool is_difficult()
{
    string s;
    getline(cin, s);
    for (int i = 0;i < s.length();i++)
    {
        if (i % 2 == 0)
        {
            if (s[i] < 97 || s[i] > 122)
            {
                return false;
            }
        }
        else
        {
            if (s[i] < 65 || s[i] > 90)
            {
                return false;
            }
        }
    }
    return true;
}

void solve()
{
    if (is_difficult())
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}

int main()
{
    solve();
    return 0;
}