#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

class Kosaraju {
private:
    int n;
public:
    vector<vector<size_t>> graph;
    vector<vector<size_t>> transpose_graph;
    vector<bool> visited;
    vector<size_t> forward_order;
    vector<size_t> backward_order;
    vector<size_t> reverse_backward_order;
    size_t backward_cnt;
    size_t forward_cnt;

    Kosaraju(int n) : n(n)
    {
        graph.resize(n);
        transpose_graph.resize(n);
        visited.resize(n, false);
        forward_order.resize(n);
        backward_order.resize(n);
        reverse_backward_order.resize(n);
        backward_cnt = 0;
        forward_cnt = 0;
    }
    void add_edge(int u, int v)
    {
        graph[u].push_back(v);
        transpose_graph[u].push_back(v);    // 原本以为要在逆向图里搜索，实际是正向图，请忽略命名造成的误解
    }
    void dfs(size_t u)
    {
        visited[u] = true;
        forward_order[u] = ++forward_cnt;
        for (size_t v : graph[u])
        {
            if (!visited[v])
            {
                dfs(v);
            }
        }
        backward_order[u] = ++backward_cnt;
    }
    void dfs2(size_t u)
    {
        visited[u] = true;
        for (size_t v : transpose_graph[u])
        {
            if (!visited[v])
            {
                dfs2(v);
            }
        }
    }
    
    void get_reverse_order()
    {
        visited.resize(n, false);
        forward_order.resize(n);
        backward_order.resize(n);
        reverse_backward_order.resize(n);
        backward_cnt = 0;
        forward_cnt = 0;
        for (size_t i = 0; i < graph.size(); i++)
        {
            if (!visited[i])
            {
                dfs(i);
            }
        }
        auto tem = vector<size_t>(backward_order.size());
        for (size_t i = 0; i < graph.size(); i++)
        {
            tem[backward_order[i] - 1] = i + 1;
        }

        for (size_t i = 0; i < graph.size(); i++)
        {
            reverse_backward_order[i] = tem[graph.size() - 1 - i];
        }
    }
    int get_strongly_connected_components()
    {
        get_reverse_order();
        int ans = 0;
        visited.assign(n, false);
        for (size_t i = 0; i < reverse_backward_order.size(); i++)
        {
            if (!visited[reverse_backward_order[i] - 1])
            {
                ans++;
                dfs2(reverse_backward_order[i] - 1);
            }
        }
        return ans;
    }
};


void solve()
{
    int n;
    cin >> n;
    int m;
    cin >> m;
    Kosaraju kosaraju(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        kosaraju.add_edge(u - 1, v - 1);
    }
    cout << kosaraju.get_strongly_connected_components() << endl;
    // for (auto i : kosaraju.reverse_backward_order)
    // {
    //     cout << i << " ";
    // }
}

int main()
{
    solve();
    return 0;
}