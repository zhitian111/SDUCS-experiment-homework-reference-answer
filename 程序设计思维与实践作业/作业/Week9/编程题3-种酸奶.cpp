#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>
#include <vector>
#include <limits>
using namespace std;
const int INF = numeric_limits<int>::max();
class Edge
{
public:
    Edge* next = nullptr;
    int to = -1;
    int weight = -1;
    Edge(){};
    Edge(int to, int weight, Edge *next): to(to), weight(weight), next(next){};
};
int n, m;
vector<Edge> edges(2000);
queue<int> q;
int dis[2000];


void addEdge(int x, int y, int weight)
{
  edges[x].next = new Edge(y, weight, edges[x].next);
}

bool SPFA()
{
    bool visited[2000];
    int cnt[2000];
    for (int i = 0; i <= n; ++i)
    {
        cnt[i] = 0;
        visited[i] = false;
    }
    q.emplace(0);
    visited[0] = true;
    for (int i = 0; i <= n; ++i)
    {
        dis[i] = INF;
    }
    dis[0] = 0;
    while (!q.empty())
    {
        int tmp = q.front();
        q.pop();
        visited[tmp] = false;
        Edge *last = &edges[tmp];
        Edge *now = edges[tmp].next;
        while ((now != nullptr) && (now->to != -1))
        {
        if (dis[tmp] + now->weight < dis[now->to])
        {
            dis[now->to] = dis[tmp] + now->weight;
            cnt[now->to] = cnt[tmp] + 1;
            if (cnt[now->to] > n + 1)
            {
            return false;
            }
            if (!visited[now->to])
            {
            q.emplace(now->to);
            visited[now->to] = true;
            }
        }
        last = now;
        now = now->next;
        }
    }
    return true;
}

void solve()
{
    cin >> n >> m;
    for (int i = 0; i <= n; ++i)
    {
        edges[i].next = new Edge(-1, 0, nullptr);
    }
    for (int i = 1; i <= n; ++i)
    {
        addEdge(i - 1, i, 1);
        addEdge(i, i - 1, 0);
    }
    for (int i = 1; i <= m; ++i)
    {
        int k, a, b, c;
        cin >> k >> a >> b >> c;
        if (k == 1)
        {
            addEdge(a - 1, b, c);
        }
        if (k == 2)
        {
            addEdge(b, a - 1, -c);
        }
        if (k == 3)
        {
            addEdge(a - 1, b, c - 1);
        }
        if (k == 4)
        {
            addEdge(b, a - 1, -1 - c);
        }
        if (k == 5)
        {
            addEdge(b, a - 1, -c);
            addEdge(a - 1, b, c);
        }
    }
    if (SPFA())
    {
        cout << dis[n] << endl;
    }
    else
    {
        cout << "impossible" << endl;
    }
}

int main()
{
    solve();
    return 0;
}