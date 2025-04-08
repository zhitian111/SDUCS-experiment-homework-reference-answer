#include <iostream>
#include <vector>

using namespace std;
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a;
    if(k==1)
    {
        cout << n << endl;
        return;
    }
    for (int i = 0; i < n; i++)
    {
        a.push_back(i + 1);
    }
    int count = 1;
    while (a.size() > 1)
    {
        vector<int> b;
        for (auto i : a)
        {
            if (count % 10 != k && count % k != 0)
            {
                b.push_back(i);
            }
            count++;
        }
        a = b;
    }
    cout << a[0] << endl;
}

int main()
{
    solve();
    return 0;
}