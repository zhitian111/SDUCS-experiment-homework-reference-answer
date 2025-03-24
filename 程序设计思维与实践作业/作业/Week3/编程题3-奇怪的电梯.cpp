#include <iostream>
#include <queue>
using namespace std;

struct node
{
    int num;
    int step;
};

void solve()
{
    int mark;
    while (true)
    {
        cin >> mark;
        if (mark == 0)
        {
            return;
        }
        int n;
        n = mark;
        int up_side = n;
        int down_side = 1;
        int from, to;
        cin >> from >> to;

        int k[n + 1];
        for (int i = 1; i <= n; i++)
        {
            cin >> k[i];
        }
        if (from == to)
        {
            cout << 0 << endl;
            continue;
        }
        int tem;
        bool can_reach[n + 1] = { false };
        bool reach = false;
        can_reach[from] = true;
        queue<node> q;
        q.push({ from,0 });
        while (!q.empty())
        {
            node cur = q.front();
            q.pop();
            if (cur.num == to)
            {
                reach = true;
            }
            if (reach)
            {
                cout << cur.step << endl;
                break;
            }
            int next_floor = cur.num + k[cur.num];
            if (next_floor <= up_side && next_floor >= down_side && can_reach[next_floor] == false)
            {
                q.push({ next_floor, cur.step + 1 });
                can_reach[next_floor] = true;
            }
            next_floor = cur.num - k[cur.num];
            if (next_floor >= 1 && next_floor <= up_side && can_reach[next_floor] == false)
            {
                q.push({ next_floor, cur.step + 1 });
                can_reach[next_floor] = true;
            }
        }
        if (!reach)
        {
            cout << -1 << endl;
        }
    }
    
    
}

int main()
{
    solve();
    return 0;
}