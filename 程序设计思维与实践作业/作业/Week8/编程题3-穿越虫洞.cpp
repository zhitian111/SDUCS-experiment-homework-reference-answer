#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;
template<typename T, bool Directed = false, bool Weighted = false, typename weight_type = int>
class Graph
{
public:
    struct Edge
    {
        size_t from, to;
        weight_type weight = 0;
        bool operator<(const Edge& rhs) const
        {
            return weight < rhs.weight;
        }
        bool operator>(const Edge& rhs) const
        {
            return weight > rhs.weight;
        }

    };
    struct Node
    {
        T data;
        vector<Edge> edges;
    };
    std::vector<Node> nodes;
    std::vector<Edge> edges;

    void addNode(const T& data)
    {
        nodes.emplace_back(Node{ data, {} });
    }

    void addEdge(size_t from, size_t to, const weight_type& weight = 0);
    bool isExistInverseRing() const;
    void print() const;
    // void SPFA(size_t start, size_t end) const;
};

template <typename T, bool Directed, bool Weighted, typename weight_type>
void Graph<T, Directed, Weighted, weight_type>::addEdge(size_t from, size_t to, const weight_type& weight)
{

    if (!Directed)  // 无向图
    {
        if (Weighted)   // 无向加权图
        {
            nodes[from - 1].edges.push_back({ from ,to, weight });
            nodes[to - 1].edges.push_back({to,from, weight});
            edges.emplace_back(Edge{ to, from, weight });
            edges.emplace_back(Edge{ from, to, weight });
        }
        else        // 无向无权图
        {
            nodes[from - 1].edges.push_back({ from ,to});
            nodes[to - 1].edges.push_back({to,from});
            edges.emplace_back(Edge{ from, to });
            edges.emplace_back(Edge{ to, from });
        }
    }
    else        // 有向图
    {
        if (Weighted)   // 有向加权图
        {
            nodes[from - 1].edges.push_back(Edge{ from, to, weight });
            edges.emplace_back(Edge{ from, to, weight });
        }
        else          // 有向无权图
        {
            nodes[from - 1].edges.push_back(Edge{ from, to });
            edges.emplace_back(Edge{ from, to });
        }
    }
}

template <typename T, bool Directed, bool Weighted, typename weight_type>
void Graph<T, Directed, Weighted, weight_type>::print() const
{
    for (size_t i = 0; i < nodes.size(); i++)
    {
        cout << "节点：" << nodes[i].data << "\n\t边:\n";
        if (Weighted)
        {
            for (auto& edge : nodes[i].edges)
            {
                cout << "\t(" << edge.from << "," << edge.to << "," << edge.weight << ")" << endl;
            }
        }
        else
        {
            for (auto& edge : nodes[i].edges)
            {
                cout << "\t(" << edge.from << "," << edge.to << ")" << endl;
            }
        }
        
        cout << endl;
    }
}

template <typename T, bool Directed, bool Weighted, typename weight_type>
bool Graph<T, Directed, Weighted, weight_type>::isExistInverseRing() const
{
    if (Weighted)
    {
        // 队列优化的BellManFord算法
        auto isExist = false;
        auto edges = this->edges;
        auto nodes = this->nodes;
        queue<Node> nodes_q;
        const auto INF = numeric_limits<weight_type>::max();
        nodes.push_back(Node{ nodes.size(), {} });
        for (size_t i = 0; i < nodes.size() - 1; i++)
        {
            nodes.back().edges.push_back(Edge{ nodes.size(), i + 1 , 0 });
        }
        nodes_q.push(nodes.back());
        auto dist = vector<weight_type>(nodes.size(), INF);
        auto cnt = vector<size_t>(nodes.size(), 0);
        dist[nodes.size() - 1] = 0;
        while (!nodes_q.empty())
        {
            auto node = nodes_q.front();
            nodes_q.pop();
            for (auto& edge : node.edges)
            {
                if (dist[edge.from - 1] != INF && dist[edge.to - 1] > dist[edge.from - 1] + edge.weight)
                {
                    dist[edge.to - 1] = dist[edge.from - 1] + edge.weight;
                    nodes_q.push(nodes[edge.to - 1]);
                    cnt[edge.to - 1]++;
                    if (cnt[edge.to - 1] > nodes.size() - 1)
                    {
                        isExist = true;
                        break;
                    }
                }
            }
            if (isExist)
            {
                break;
            }
        }
        return isExist;
    }
}

void solve()
{
    size_t F;
    cin >> F;
    for (size_t loop = 0; loop < F; loop++)
    {
        size_t n, m, w;
        cin >> n >> m >> w;
        Graph<size_t, true, true, long long> graph;
        for (size_t i = 1; i <= n; i++)
        {
            graph.addNode(i);
        }
        for (size_t i = 0; i < m; i++)
        {
            size_t u, v;
            long long weight;
            cin >> u >> v >> weight;
            graph.addEdge(u, v, weight);
            graph.addEdge(v, u, weight);
        }
        for (size_t i = 0; i < w; i++)
        {
            size_t u, v;
            long long weight;
            cin >> u >> v >> weight;
            graph.addEdge(u, v, -weight);
        }
        // graph.print();
        if (graph.isExistInverseRing())
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
}

int main()
{
    solve();
    return 0;
}