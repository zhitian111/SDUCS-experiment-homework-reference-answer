/*2024数据结构--数据智能 实验13 最小生成树 A Prime算法*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>


using namespace std;

struct GraphEdgeWithCost
{
    size_t from;
    size_t to;
    size_t cost;
    bool operator<(const GraphEdgeWithCost& other) const;
    bool operator==(const GraphEdgeWithCost& other) const;
    bool operator!=(const GraphEdgeWithCost& other) const;
    bool operator>(const GraphEdgeWithCost& other) const;
};

bool GraphEdgeWithCost::operator<(const GraphEdgeWithCost& other) const
{
    return cost < other.cost;
}

bool GraphEdgeWithCost::operator==(const GraphEdgeWithCost& other) const
{
    return from == other.from && to == other.to && cost == other.cost;
}

bool GraphEdgeWithCost::operator!=(const GraphEdgeWithCost& other) const
{
    return !(*this == other);
}

bool GraphEdgeWithCost::operator>(const GraphEdgeWithCost& other) const
{
    return cost > other.cost;
}

template<typename T>
struct GraphNode
{
    T data;
    size_t id;
    vector<GraphEdgeWithCost> edges;
    vector<size_t> neighbors;
    size_t group;
    void addEdge(size_t to, size_t cost);
    void deleteEdge(size_t to);
    void printId();
    void printEdges();
    void printData();
    void print();
};

template<typename T>
void GraphNode<T>::print()
{
    printId();
    printData();
    printEdges();
}

template<typename T>
void GraphNode<T>::printId()
{
    cout << "NODE ID: " << id << endl;
}

template<typename T>
void GraphNode<T>::printData()
{
    cout <<"NODE DATA: " << data << endl;
}

template<typename T>
void GraphNode<T>::printEdges()
{
    cout << "NODE EDGES: " << endl;
    for (auto& e : edges)
    {
        cout << e.from << "->" << e.to << " (" << e.cost << ")" << endl;
    }
}


template<typename T>
void GraphNode<T>::addEdge(size_t to, size_t cost)
{
    edges.push_back({ id, to, cost });
    neighbors.push_back(to);
}

template<typename T>
void GraphNode<T>::deleteEdge(size_t to)
{
    auto it = find_if(edges.begin(), edges.end(), [to](const GraphEdgeWithCost& e) { return e.to == to; });
    if (it!= edges.end())
    {
        edges.erase(it);
        auto it2 = find(neighbors.begin(), neighbors.end(), to);
        if (it2!= neighbors.end())
        {
            neighbors.erase(it2);
        }
    }
}


template<typename T>
class GraphWithCostEdges        //实际是无向图
{
private:
    vector<GraphNode<T>> nodes;
    bool connected;
public:
    GraphWithCostEdges() {}
    GraphWithCostEdges(size_t n);
    void addEdge(size_t from, size_t to, size_t cost);
    void deleteEdge(size_t from, size_t to);
    void printGraph();

    bool isConnected();
    void checkConnected();
    
    size_t prim();
    size_t kruskal();
};

template<typename T>
GraphWithCostEdges<T>::GraphWithCostEdges(size_t n)
{
    connected = true;
    nodes.resize(n + 1);
    for (size_t i = 1; i <= n; i++)
    {
        nodes[i].id = i;
        nodes[i].data = i;
    }
}

template<typename T>
void GraphWithCostEdges<T>::addEdge(size_t from, size_t to, size_t cost)
{
    nodes[from].addEdge(to, cost);
    nodes[to].addEdge(from, cost);
}

template<typename T>
void GraphWithCostEdges<T>::deleteEdge(size_t from, size_t to)
{
    nodes[from].deleteEdge(to);
    nodes[to].deleteEdge(from);
}

template<typename T>
void GraphWithCostEdges<T>::printGraph()
{
    for (auto& node : nodes)
    {
        node.print();
    }
}

template<typename T>
bool GraphWithCostEdges<T>::isConnected()
{
    return connected;
}

template<typename T>
size_t GraphWithCostEdges<T>::prim()
{
    if (!isConnected())
    {
        return 0;
    }
    size_t mst_cost = 0;
    //下为朴素Prim算法
    /*
    vector<bool> visited(nodes.size(), false);
    vector<size_t> selected;
    selected.push_back(1);
    visited[0] = true;
    visited[1] = true;
    while (selected.size() < nodes.size() - 1)
    {
        size_t min_cost = numeric_limits<size_t>::max();
        GraphEdgeWithCost* min_edge = nullptr;
        for (auto& node_index : selected)
        {
            for (auto& edge : nodes[node_index].edges)
            {
                if (!visited[edge.to])
                {
                    if (edge.cost < min_cost)
                    {
                        min_cost = edge.cost;
                        min_edge = &edge;
                    }
                }
            }
        }
        selected.push_back(min_edge->to);
        visited[min_edge->to] = true;
        mst_cost += min_edge->cost;
        // cout << "Selected: " << min_edge->from << "->" << min_edge->to << " (" << min_edge->cost << ")" << endl;
    }
    */
    //下为堆优化Prim算法
    priority_queue<GraphEdgeWithCost, vector<GraphEdgeWithCost>, greater<GraphEdgeWithCost>> edges;
    vector<bool> visited(nodes.size(), false);
    visited[0] = true;
    visited[1] = true;
    vector<size_t> selected;
    selected.push_back(1);
    for (auto& edge : nodes[1].edges)
    {
        edges.push(edge);
    }
    while (selected.size() < nodes.size() - 1)
    {
        if (edges.empty())
        {
            break;
        }
        const GraphEdgeWithCost& selected_edge = edges.top();
        if (visited[selected_edge.to])
        {
            edges.pop();
            continue;
        }
        else
        {
            selected.push_back(selected_edge.to);
            visited[selected_edge.to] = true;
            mst_cost += selected_edge.cost;
            for (auto& edge : nodes[selected_edge.to].edges)
            {
                if (!visited[edge.to])
                {
                    edges.push(edge);
                }
            }
        }
    }

    return mst_cost;
}

template<typename T>
size_t GraphWithCostEdges<T>::kruskal()
{
    if (!isConnected())
    {
        return 0;
    }
    size_t mst_cost = 0;

    priority_queue<GraphEdgeWithCost, vector<GraphEdgeWithCost>, greater<GraphEdgeWithCost>> edges;
    vector<bool> visited(nodes.size(), false);
    while (!edges.empty())
    {    
        if (visited[edges.top().from] && visited[edges.top().to])
        {
            edges.pop();
            continue;
        }
        const GraphEdgeWithCost& edge = edges.top();
        visited[edge.from] = true;
        visited[edge.to] = true;
        mst_cost += edge.cost;
        edges.pop();
    }
    return mst_cost;
}

template<typename T>
void GraphWithCostEdges<T>::checkConnected()
{
    queue<size_t> q;
    q.push(1);
    vector<bool> visited(nodes.size(), false);
    visited[0] = true;
    visited[1] = true;
    while (!q.empty())
    {
        size_t u = q.front();
        q.pop();
        for (auto& e : nodes[u].edges)
        {
            if (!visited[e.to])
            {
                visited[e.to] = true;
                q.push(e.to);
            }
        }
    }

    for (bool v : visited)
    {
        if (!v)
        {
            connected = false;
            return;
        }
    }
    connected = true;
}


class Solution
{
public:
    void solve();
};

void Solution::solve()
{
    ios::sync_with_stdio(false);
    size_t n, e;
    cin >> n >> e;
    GraphWithCostEdges<int> graph(n);
    for (size_t i = 0; i < e; i++)
    {
        size_t from, to, cost;
        cin >> from >> to >> cost;
        graph.addEdge(from, to, cost);
    }
    // graph.printGraph();
    // graph.checkConnected();
    // cout << "Is connected: " << graph.isConnected() << endl;
    // cout << "MST cost: " << graph.prim() << endl;
    cout << graph.prim() << endl;
    // cout << graph.kruskal() << endl;
}

int main()
{
    Solution solution;
    solution.solve();
    return 0;
}
