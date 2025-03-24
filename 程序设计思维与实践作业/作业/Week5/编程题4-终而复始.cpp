#include <iostream>
#include <stack>
#include <limits>
using namespace std;

void solve()
{
    long long n;
    cin >> n;
    struct node
    {
        long long val;
        long long index;
        long long left_first_less;
        long long right_first_less;
    };
    node nodes[n];
    for (long long i = 0; i < n; i++)
    {
        cin >> nodes[i].val;
        nodes[i].index = i;
        nodes[i].left_first_less = -1;
        nodes[i].right_first_less =  n;
    }
    stack<node> s;
    s.push(nodes[0]);
    for (long long i = 1; i < n; i++)
    {
        if (nodes[i].val < s.top().val)
        {
            while (!s.empty() && s.top().val >= nodes[i].val)
            {
                s.pop();
            }
            if (!s.empty())
            {
                nodes[i].left_first_less = s.top().index;
            }
            s.push(nodes[i]);
        }
        if (nodes[i].val == s.top().val)
        {
            if (s.empty())
            {
                s.push(nodes[i]);
                continue;
            }
            nodes[i].left_first_less = s.top().left_first_less;
            s.push(nodes[i]);
        }
        if (nodes[i].val > s.top().val)
        {
            if (s.empty())
            {
                s.push(nodes[i]);
                continue;
            }
            nodes[i].left_first_less = s.top().index;
            s.push(nodes[i]);
        }
    }
    stack<node> s2;
    s2.push(nodes[n - 1]);
    for (long long i = n - 2; i >= 0; i--)
    {
        if (nodes[i].val > s2.top().val)
        {
            if (s2.empty())
            {
                s2.push(nodes[i]);
                continue;
            }
            nodes[i].right_first_less = s2.top().index;
            s2.push(nodes[i]);
        }
        if (nodes[i].val == s2.top().val)
        {
            if (s2.empty())
            {
                s2.push(nodes[i]);
                continue;
            }
            nodes[i].right_first_less = s2.top().right_first_less;
            s2.push(nodes[i]);
        }
        if (nodes[i].val < s2.top().val)
        {
            while (!s2.empty() && s2.top().val >= nodes[i].val)
            {
                s2.pop();
            }
            if (!s2.empty())
            {
                nodes[i].right_first_less = s2.top().index;
            }
            s2.push(nodes[i]);
        }
    }
    // for (auto i : nodes)
    // {
    //     cout << i.left_first_less << " ";
    // }
    // cout << endl;
    // for (auto i : nodes)
    // {
    //     cout << i.right_first_less << " ";
    // }
    // cout << endl;
    long long best = numeric_limits<long long>::min();
    for (long long i = 0; i < n; i++)
    {
        best = max(best, nodes[i].val * (nodes[i].right_first_less - nodes[i].left_first_less - 1));
    }
    cout << best;
}

int main()
{
    solve();
    return 0;
}