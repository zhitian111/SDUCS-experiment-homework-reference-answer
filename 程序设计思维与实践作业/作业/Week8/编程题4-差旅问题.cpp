#include <iostream>
using namespace std;
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
    std::vector<std::vector<weight_type>> floyd();
    weight_type dijkstra_for_end(size_t start, size_t end) const;
    std::vector<weight_type> dijkstra_no_end(size_t start) const;
    weight_type spfa_for_end(size_t start, size_t end) const;
    std::vector<weight_type> spfa_no_end(size_t start) const;
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

template <typename T, bool Directed, bool Weighted, typename weight_type>
std::vector<std::vector<weight_type>> Graph<T, Directed, Weighted, weight_type>::floyd()
{
    auto dist = vector<vector<weight_type>>(nodes.size(), vector<weight_type>(nodes.size(), numeric_limits<weight_type>::max()));
    for (auto& edge : edges)
    {
        dist[edge.from - 1][edge.to - 1] = edge.weight;
    }
    for (size_t i = 0; i < nodes.size(); i++)
    {
        dist[i][i] = 0;
    }
    for (size_t k = 0; k < nodes.size(); k++)
    {
        for (size_t i = 0; i < nodes.size(); i++)
        {
            for (size_t j = 0; j < nodes.size(); j++)
            {
                if (dist[i][k] != numeric_limits<weight_type>::max() && dist[k][j] != numeric_limits<weight_type>::max() && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return dist;
}

template <typename T, bool Directed, bool Weighted, typename weight_type>
weight_type Graph<T, Directed, Weighted, weight_type>::dijkstra_for_end(size_t start, size_t end) const
{
    auto dist = vector<weight_type>(nodes.size(), numeric_limits<weight_type>::max());
#include <queue>
    priority_queue<pair<weight_type, size_t>,
            vector<pair<weight_type, size_t>>,
            greater<pair<weight_type, size_t>>>
                                                q;
    q.push(make_pair(0, start));
    while (!q.empty())
    {
        auto node = q.top();
        q.pop();
        if (dist[node.second - 1] == numeric_limits<weight_type>::max())
        {
            dist[node.second - 1] = node.first;
            for (auto& edge : nodes[node.second - 1].edges)
            {
                q.push(make_pair(node.first + edge.weight, edge.to));
            }
        }
        if (node.second == end)
        {
            break;
        }
        if (dist[node.second - 1] != numeric_limits<weight_type>::max())
        {
            for (auto& edge : nodes[node.second - 1].edges)
            {
                if (dist[edge.to - 1] == numeric_limits<weight_type>::max())
                {
                    q.push(make_pair(node.first + edge.weight, edge.to));
                }
            }
        }
        if (node.second == end)
        {
            break;
        }
    }
    return dist[end - 1];
}
template <typename T, bool Directed, bool Weighted, typename weight_type>
std::vector<weight_type> Graph<T, Directed, Weighted, weight_type>::dijkstra_no_end(size_t start) const
{
    auto dist = vector<weight_type>(nodes.size(), numeric_limits<weight_type>::max());
#include <queue>
    priority_queue<pair<weight_type, size_t>,
            vector<pair<weight_type, size_t>>,
            greater<pair<weight_type, size_t>>>
                                                q;
    q.push(make_pair(0, start));
    while (!q.empty())
    {
        auto node = q.top();
        q.pop();
        if (dist[node.second - 1] == numeric_limits<weight_type>::max())
        {
            dist[node.second - 1] = node.first;
            for (auto& edge : nodes[node.second - 1].edges)
            {
                q.push(make_pair(node.first + edge.weight, edge.to));
            }
        }
        if (dist[node.second - 1] != numeric_limits<weight_type>::max())
        {
            for (auto& edge : nodes[node.second - 1].edges)
            {
                if (dist[edge.to - 1] == numeric_limits<weight_type>::max())
                {
                    q.push(make_pair(node.first + edge.weight, edge.to));
                }
            }
        }
    }
    return dist;
}

template <typename T, bool Directed, bool Weighted, typename weight_type>
vector<weight_type> Graph<T, Directed, Weighted, weight_type>::spfa_no_end(size_t start) const
{
    if (Weighted)
    {
        deque<Node> nodes_q;
        const auto INF = numeric_limits<weight_type>::max();
        vector<weight_type> dist(nodes.size(), INF);
        vector<bool> in_queue(nodes.size(), false);
        vector<size_t> cnt(nodes.size(), 0);
        nodes_q.push_back(nodes[start - 1]);
        dist[start - 1] = 0;
        in_queue[start - 1] = true;
        while (!nodes_q.empty())
        {
            auto node = nodes_q.front();
            nodes_q.pop_front();
            in_queue[node.data - 1] = false;
            for (auto& edge : node.edges)
            {
                if (dist[edge.from - 1] != INF && dist[edge.to - 1] > dist[edge.from - 1] + edge.weight)
                {
                    dist[edge.to - 1] = dist[edge.from - 1] + edge.weight;
                    if (!in_queue[edge.to - 1])
                    {
                        nodes_q.push_back(nodes[edge.to - 1]);
                        in_queue[edge.to - 1] = true;
                        cnt[edge.to - 1]++;
                        if (cnt[edge.to - 1] > nodes.size() - 1)
                        {
                            break;
                        }
                    }
                }
            }
        }
        return dist;
    }
}

template <typename T, bool Directed, bool Weighted, typename weight_type>
weight_type Graph<T, Directed, Weighted, weight_type>::spfa_for_end(size_t start, size_t end) const
{
    if (Weighted)
    {
        deque<Node> nodes_q;
        const auto INF = numeric_limits<weight_type>::max();
        vector<weight_type> dist(nodes.size(), INF);
        vector<bool> in_queue(nodes.size(), false);
        vector<size_t> cnt(nodes.size(), 0);
        nodes_q.push_back(nodes[start - 1]);
        dist[start - 1] = 0;
        in_queue[start - 1] = true;
        while (!nodes_q.empty())
        {
            auto node = nodes_q.front();
            nodes_q.pop_front();
            in_queue[node.data - 1] = false;
            for (auto& edge : node.edges)
            {
                if (dist[edge.from - 1] != INF && dist[edge.to - 1] > dist[edge.from - 1] + edge.weight)
                {
                    dist[edge.to - 1] = dist[edge.from - 1] + edge.weight;
                    if (!in_queue[edge.to - 1])
                    {
                        nodes_q.push_back(nodes[edge.to - 1]);
                        in_queue[edge.to - 1] = true;
                        cnt[edge.to - 1]++;
                        if (cnt[edge.to - 1] > nodes.size() - 1)
                        {
                            break;
                        }
                    }
                }
            }
        }
        if (dist[end - 1] != INF)
        {
            return dist[end - 1];
        }
    }
}

void solve()
{
    size_t N;
    cin >> N;
    for (size_t i = 0; i < N; i++)
    {
        Graph<size_t, true, true, size_t> graph_reverse;
        Graph<size_t, true, true, size_t> graph;
        size_t n, m;
        cin >> n >> m;
        for (size_t j = 0; j < n; j++)
        {
            graph.addNode(j + 1);
            graph_reverse.addNode(j + 1);
        }
        for (size_t j = 0; j < m; j++)
        {
            size_t from = 0, to = 0, weight = 0;
            cin >> from >> to >> weight;
            graph.addEdge(from, to, weight);
            graph_reverse.addEdge(to, from, weight);
        }

        size_t sum = 0;
        // auto dist = graph.dijkstra_no_end(1);
        auto dist = graph.spfa_no_end(1);
        auto dist_reverse = graph_reverse.spfa_no_end(1);
        for (size_t j = 1; j < n; j++)
        {
            sum += dist[j];
            sum += dist_reverse[j];
        }
        cout << sum << endl;
    }
}
int main()
{
    solve();
    return 0;
}