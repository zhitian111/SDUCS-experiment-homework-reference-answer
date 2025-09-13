#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<priority_queue<int,vector<int>,greater<int>>> buckets(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        buckets[y - 1].push(x);
    }
    for (auto& bucket : buckets)
    {
        while (!bucket.empty())
        {
            cout << bucket.top() << " ";
            bucket.pop();
        }
        cout << endl;
    }
}

int main()
{
    solve();
    return 0;
}