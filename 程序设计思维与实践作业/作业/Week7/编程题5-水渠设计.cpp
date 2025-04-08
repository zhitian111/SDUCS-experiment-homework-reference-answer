#include <iostream>
#include <vector>
#include <stddef.h>
#include <queue>
using namespace std;


template<typename T, bool Directed = false, bool Weighted = false>
class Graph
{
public:
    struct Node
    {
        T data;
        vector<size_t> edge;
    };
    struct Edge
    {
        size_t from, to;
        size_t weight = 0;
        bool operator<(const Edge& rhs) const
        {
            return weight < rhs.weight;
        }
        bool operator>(const Edge& rhs) const
        {
            return weight > rhs.weight;
        }
    };

    vector<Node> nodes;
    vector<Edge> edges;

    void addNode(const T& data)
    {
        nodes.emplace_back(Node{ data, {} });
    }

    void addEdge(size_t from, size_t to, const size_t& weight = 0);
    void print() const;
};

template <typename T, bool Directed, bool Weighted>
void Graph<T, Directed, Weighted>::addEdge(size_t from, size_t to, const size_t& weight)
{

    if (!Directed)  // 无向图
    {
        nodes[from - 1].edge.push_back(to);
        nodes[to - 1].edge.push_back(from);
        if (Weighted)   // 无向加权图
        {
            edges.emplace_back(Edge{ to, from, weight });
            edges.emplace_back(Edge{ from, to, weight });
        }
        else        // 无向无权图
        {
            edges.emplace_back(Edge{ from, to });
            edges.emplace_back(Edge{ to, from });
        }
    }
    else        // 有向图
    {
        if (Weighted)   // 有向加权图
        {
            edges.emplace_back(Edge{ from, to, weight });
        }
        else          // 有向无权图
        {
            edges.emplace_back(Edge{ from, to });
        }
    }
}

template <typename T, bool Directed, bool Weighted>
void Graph<T, Directed, Weighted>::print() const
{
    for (size_t i = 0; i < nodes.size(); i++)
    {
        cout << nodes[i].data << ": ";
        for (size_t j = 0; j < nodes[i].edge.size(); j++)
        {
            cout << nodes[i].edge[j] << " ";
        }
        cout << endl;
    }
}


template<typename T>
class UnionFindSet
{
public:
    class UnionFindNode
    {
    public:
        T data;
        size_t parent;
    };
    size_t type_cnt;
    std::vector<UnionFindNode> nodes;
    UnionFindSet<T>() : nodes(0), type_cnt(0) {}
    UnionFindSet<T>(size_t n) : nodes(n), type_cnt(n)
    {
        for (size_t i = 0; i < n; i++)
        {
            nodes[i].parent = i;
        }
    }
    void merge(size_t x, size_t y);
    bool is_same_set(size_t x, size_t y);
};

template<typename T>
void UnionFindSet<T>::merge(size_t x, size_t y)
{
    if (x == y)
    {
        return;
    }
    auto x_parent = nodes[x].parent;
    auto y_parent = nodes[y].parent;
    while (x_parent != nodes[x_parent].parent)
    {
        x_parent = nodes[x_parent].parent;
    }
    while (y_parent != nodes[y_parent].parent)
    {
        y_parent = nodes[y_parent].parent;
    }
    nodes[x].parent = x_parent;
    nodes[y].parent = y_parent;
    if (x_parent < y_parent)
    {
        nodes[y_parent].parent = x_parent;
    }
    else if (x_parent > y_parent)
    {
        nodes[x_parent].parent = y_parent;
    }
    if (x_parent != y_parent)
    {
        type_cnt--;
    }
    return;
}

template<typename T>
bool UnionFindSet<T>::is_same_set(size_t x, size_t y)
{
    auto x_parent = nodes[x].parent;
    auto y_parent = nodes[y].parent;
    while (x_parent != nodes[x_parent].parent)
    {
        x_parent = nodes[x_parent].parent;
    }
    while (y_parent != nodes[y_parent].parent)
    {
        y_parent = nodes[y_parent].parent;
    }
    nodes[x].parent = x_parent;
    nodes[y].parent = y_parent;
    return x_parent == y_parent;
}
void solve()
{
    size_t n, m, p;
    cin >> n >> m >> p;
    Graph<size_t, true, true> graph;
    for (size_t i = 1; i < n + 1; i++)
    {
        graph.addNode(i);
    }
    
    for (size_t i = 0; i < m; i++)
    {
        size_t from, to, weight;
        cin >> from >> to >> weight;
        graph.addEdge(from, to, weight);
    }
    // graph.print();
    priority_queue<Graph<size_t, true, true>::Edge, vector<Graph<size_t, true, true>::Edge>, greater<Graph<size_t, true, true>::Edge>> pq;
    for (auto& i : graph.edges)
    {
        if (i.weight <= p)
        {
            pq.push(i);
        }
    }
    vector<bool> visited(n, false);
    UnionFindSet<size_t> ufs(n);
    size_t sum = 0;
    while (!pq.empty())
    {
        auto edge = pq.top();
        pq.pop();
        if (ufs.is_same_set(edge.from - 1, edge.to - 1))
        {
            continue;
        }
        else
        {
            ufs.merge(edge.from - 1, edge.to - 1);
            sum += edge.weight;
            // cout << "merge" << edge.from << " " << edge.to << endl;
        }
    }
    auto ans = sum + ufs.type_cnt * p;
    cout << ans << endl;
}

int main()
{
    solve();
    return 0;
}