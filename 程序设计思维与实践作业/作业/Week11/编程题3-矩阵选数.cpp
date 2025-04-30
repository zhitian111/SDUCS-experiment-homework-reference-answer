#include <iostream>
#include <vector>
using namespace std;

void solve()
{
    vector<vector<int>> arr;
    int n;
    cin >> n;
    arr.resize(3);
    arr[0].resize(n);
    arr[1].resize(n);
    arr[2].resize(n);
    for (int i = 0;i < n;i++)
    {
        cin >> arr[0][i];
    }
    for (int i = 0;i < n;i++)
    {
        cin >> arr[1][i];
    }
    for (int i = 0;i < n;i++)
    {
        cin >> arr[2][i];
    }
    
}
int main()
{
    solve();
    return 0;
}