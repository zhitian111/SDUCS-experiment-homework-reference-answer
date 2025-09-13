#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>    
using namespace std;

struct Node
{
    vector<size_t> connected_nodes;
};
vector<size_t> bfs(Node nodes[], size_t n, size_t start)
{
    struct search_node
    {
        size_t index;
        size_t depth;
    };
    vector<size_t> depth(n, 0);
    queue<search_node> q;
    bool visited[n] = { false };
    q.push({ start - 1, 0 });
    visited[start - 1] = true;
    while (!q.empty())
    {
        auto tem = q.front();
        q.pop();
        depth[tem.index] = tem.depth;
        for (auto& j : nodes[tem.index].connected_nodes)
        {
            if (visited[j])
            {
                continue;
            }
            q.push({ j, tem.depth + 1 });
            visited[j] = true;
        }
        // cout << "index:" << tem.index << " depth:" << tem.depth << endl;
    }
    // cout << max << " ";        
    return depth;
}


void solve()
{
    size_t n;
    cin >> n;
    Node nodes[n];
    for (size_t i = 1; i < n; i++)
    {
        size_t from, to;
        cin >> from >> to;
        nodes[from - 1].connected_nodes.push_back(to - 1);
        nodes[to - 1].connected_nodes.push_back(from - 1);
    }
    auto ini = bfs(nodes, n, 1);
    size_t u = max_element(ini.begin(), ini.end()) - ini.begin() + 1;
    ini = bfs(nodes, n, u);
    size_t v = max_element(ini.begin(), ini.end()) - ini.begin() + 1;
    auto u_dis = bfs(nodes, n, u);
    auto v_dis = bfs(nodes, n, v);
    for (size_t i = 1; i <= n; i++)
    {
        size_t ans = u_dis[i - 1] > v_dis[i - 1] ? u_dis[i - 1] : v_dis[i - 1];
        cout << ans << " ";
    }

}

int main()
{
    solve();
    return 0;
}