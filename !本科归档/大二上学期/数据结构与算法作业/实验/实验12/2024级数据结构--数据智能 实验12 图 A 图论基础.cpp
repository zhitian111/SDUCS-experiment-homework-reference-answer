/*2024级数据结构--数据智能 实验12 图 A 图论基础.cpp*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

template<typename T>
struct GraphNode
{
    T data;
    //索引方案
    size_t index;
    vector<size_t> neighbors;
    //指针方案
    vector<GraphNode<T>*> neighbors_ptr;
    void addNeighbor(size_t neighbor_index);
    void delNeighbor(size_t neighbor_index);
    void addNeighbor(GraphNode<T>* neighbor_ptr);
    void delNeighbor(GraphNode<T>* neighbor_ptr);
    GraphNode() {}
    GraphNode(T data, size_t index) : data(data), index(index) {}
};

template<typename T>
void GraphNode<T>::addNeighbor(size_t neighbor_index)
{
    for (auto neighbor : neighbors)
    {
        if (neighbor == neighbor_index)
        {
            return;
        }
    }
    neighbors.push_back(neighbor_index);    
}

template<typename T>
void GraphNode<T>::delNeighbor(size_t neighbor_index)
{
    for (auto it = neighbors.begin(); it != neighbors.end(); it++)
    {
        if (*it == neighbor_index)
        {
            neighbors.erase(it);
            return;
        }
    }
}

template<typename T>
void GraphNode<T>::addNeighbor(GraphNode<T>* neighbor_ptr)
{
    neighbors_ptr.push_back(neighbor_ptr);
}

template<typename T>
void GraphNode<T>::delNeighbor(GraphNode<T>* neighbor_ptr)
{
    neighbors_ptr.erase(find(neighbors_ptr.begin(), neighbors_ptr.end(), neighbor_ptr));
}

template<typename T>
void printGraphNodeData(GraphNode<T>& node)
{
    cout << node.data << " ";
}

template<typename T>
void printGraphNodeEdges(GraphNode<T>& node)
{
    cout << "Neighbors: ";
    for (size_t i = 0; i < node.neighbors.size(); i++)
    {
        cout << node.neighbors[i] + 1 << " ";
    }
    cout << endl;
}

template<typename T>
void printGraphNode(GraphNode<T>& node)
{
    cout << "Node: " << node.data << endl;
    printGraphNodeEdges(node);
}



template<typename T>
class GraphWithoutDirection
{
private:
    vector<GraphNode<T>> nodes;
    T tem_subgraph_data;
    void subgraphMinPoints(GraphNode<T>& node);
    size_t DFSCount;
    void DFSCounter();
    size_t BFSCount;
    void BFSCounter();
public:

    vector<GraphNode<T>>& getNodes() { return nodes; }

    GraphWithoutDirection(size_t n);
    void addEdge(size_t u, size_t v);
    void delEdge(size_t u, size_t v);
    void ConnectedComponents();
    size_t DFSLength(size_t start_index);
    size_t BFSLength(size_t start_index);
    void DepthFirstSearch(size_t start_index, vector<bool>& visited, void (*operation)(GraphNode<T>& node) = nullptr);//调用类外函数
    void DepthFirstSearch(size_t start_index, vector<bool>& visited, void (GraphWithoutDirection<T>::* operation)(GraphNode<T>& node));//调用类内函数
    void DepthFirstSearch(size_t start_index, vector<bool>& visited, void (GraphWithoutDirection<T>::* operation)());//调用类内函数

    void DictionaryPrefaceDFS(size_t start_index, vector<bool>& visited, void (*operation)(GraphNode<T>& node) = nullptr);//字典序优先深搜+调用类外函数
    void DictionaryPrefaceDFS(size_t start_index, vector<bool>& visited, void (GraphWithoutDirection<T>::* operation)(GraphNode<T>& node));//字典序优先深搜+调用类内函数
    void DictionaryPrefaceDFS(size_t start_index, vector<bool>& visited, void (GraphWithoutDirection<T>::* operation)());//字典序优先深搜+调用类内函数

    void DPDFSPrint(size_t start_index);
    
    void BreadthFirstSearch(size_t start_index, vector<bool>& visited,  void (*operation)(GraphNode<T>& node) = nullptr);//调用类外函数
    void BreadthFirstSearch(size_t start_index, vector<bool>& visited,  void (GraphWithoutDirection<T>::* operation)(GraphNode<T>& node));//调用类内函数
    void BreadthFirstSearch(size_t start_index, vector<bool>& visited,  void (GraphWithoutDirection<T>::* operation)());//调用类内函数

    void DictionaryPrefaceBFS(size_t start_index, vector<bool>& visited,  void (*operation)(GraphNode<T>& node) = nullptr);//字典序优先广搜+调用类外函数
    void DictionaryPrefaceBFS(size_t start_index, vector<bool>& visited,  void (GraphWithoutDirection<T>::* operation)(GraphNode<T>& node));//字典序优先广搜+调用类内函数
    void DictionaryPrefaceBFS(size_t start_index, vector<bool>& visited,  void (GraphWithoutDirection<T>::* operation)());//字典序优先广搜+调用类内函数

    void DPBFSPrint(size_t start_index);
    
    void AllConnectivitySubgraphs();

    int Dijkstra(size_t start_index, size_t end_index);
};

template<typename T>
GraphWithoutDirection<T>::GraphWithoutDirection(size_t n)
{
    nodes.resize(n);
    for (size_t i = 0; i < n; i++)
    {
        nodes[i].index = i;
        nodes[i].data = i + 1;
        // nodes[i] = GraphNode<T>(i + 1, i);
    }
}

template<typename T>
void GraphWithoutDirection<T>::addEdge(size_t u, size_t v)
{
    nodes[u - 1].addNeighbor(v - 1);
    nodes[v - 1].addNeighbor(u - 1);
}

template<typename T>
void GraphWithoutDirection<T>::delEdge(size_t u, size_t v)
{
    nodes[u - 1].delNeighbor(v - 1);
    nodes[v - 1].delNeighbor(u - 1);
}

template<typename T>
void GraphWithoutDirection<T>::ConnectedComponents()
{
    size_t count = 0;
    vector<bool> visited(nodes.size(), false);
    for (size_t i = 0; i < nodes.size(); i++)
    {
        if (!visited[i])
        {
            count++;
            visited[i] = true;
            DepthFirstSearch
            (   i,
                visited
                // ,
                // [&](GraphNode<T>& node)
                // {
                //     visited[node.index] = true;
                // }
            );
        }
    }
    // cout << "Connected Components: " << count << endl;
    cout << count << endl;
}

template<typename T>
void GraphWithoutDirection<T>::subgraphMinPoints(GraphNode<T>& node)
{
    if (node.data < tem_subgraph_data)
    {
        tem_subgraph_data = node.data;
    }
}

template<typename T>
void GraphWithoutDirection<T>::AllConnectivitySubgraphs()
{
    vector<T> subgraph_data;
    vector<bool> visited(nodes.size(), false);
    // auto func =
    //     [&min_key](GraphNode<T>& node) mutable -> void
    //         {
    //             if (node.data < min_key)
    //             {
    //                 min_key = node.data;
    //             }
    //     };
    // void (*func_ptr)(GraphNode<T>&node) = [](GraphNode<T>& node);
    // func_ptr = func;
    for (size_t i = 0; i < nodes.size(); i++)
    {
        if (!visited[i])
        {
            tem_subgraph_data = nodes[i].data;
            visited[i] = true;
            DepthFirstSearch
            (
                i,
                visited,
                &GraphWithoutDirection<T>::subgraphMinPoints
            );
            subgraph_data.push_back(tem_subgraph_data);
        }
    }
    sort(subgraph_data.begin(), subgraph_data.end());
    // cout << "All Connectivity Subgraphs: ";
    for (auto data : subgraph_data)
    {
        cout << data << " ";
    }
    cout << endl;
}
template<typename T>
void GraphWithoutDirection<T>::DepthFirstSearch(size_t start_index, vector<bool>& visited, void (*operation)(GraphNode<T>& node))
{
    for (auto neighbor_index : nodes[start_index].neighbors)
    {
        if (!visited[neighbor_index])
        {
            visited[neighbor_index] = true;
            if (operation != nullptr)
            {
                operation(nodes[neighbor_index]);
                DepthFirstSearch(neighbor_index, visited, operation);
            }
            else
            {
                DepthFirstSearch(neighbor_index, visited);
            }
        }
    }
}

template<typename T>
void GraphWithoutDirection<T>::DepthFirstSearch(size_t start_index, vector<bool>& visited, void (GraphWithoutDirection<T>::*operation)(GraphNode<T>& node))
{
    for (auto neighbor_index : nodes[start_index].neighbors)
    {
        if (!visited[neighbor_index])
        {
            visited[neighbor_index] = true;
            if (operation != nullptr)
            {
                (this->*operation)(nodes[neighbor_index]);
                DepthFirstSearch(neighbor_index, visited, operation);
            }
            else
            {
                DepthFirstSearch(neighbor_index, visited);
            }
        }        
    }
}

template<typename T>
void GraphWithoutDirection<T>::DepthFirstSearch(size_t start_index, vector<bool>& visited, void (GraphWithoutDirection<T>::*operation)())
{
    if (operation != nullptr)
    {
        (this->*operation)();
        visited[start_index] = true;
    }
    for (auto neighbor_index : nodes[start_index].neighbors)
    {
        if (!visited[neighbor_index])
        {
            if (operation != nullptr)
            {
                DepthFirstSearch(neighbor_index, visited, operation);
            }
            else
            {
                DepthFirstSearch(neighbor_index, visited);
            }
        }
    }
}

template<typename T>
void GraphWithoutDirection<T>::DictionaryPrefaceDFS(size_t start_index, vector<bool>& visited, void (*operation)(GraphNode<T>& node))
{
    sort(nodes[start_index].neighbors.begin(), nodes[start_index].neighbors.end());
    for (auto neighbor_index : nodes[start_index].neighbors)
    {
        if (!visited[neighbor_index])
        {
            visited[neighbor_index] = true;
            if (operation != nullptr)
            {
                operation(nodes[neighbor_index]);
                DictionaryPrefaceDFS(neighbor_index, visited, operation);
            }
            else
            {
                DictionaryPrefaceDFS(neighbor_index, visited);
            }
        }
    }
}

template<typename T>
void GraphWithoutDirection<T>::DictionaryPrefaceDFS(size_t start_index, vector<bool>& visited, void (GraphWithoutDirection<T>::*operation)())
{
    sort(nodes[start_index].neighbors.begin(), nodes[start_index].neighbors.end());
    for (auto neighbor_index : nodes[start_index].neighbors)
    {
        if (!visited[neighbor_index])
        {
            visited[neighbor_index] = true;
            if (operation != nullptr)
            {
                (this->*operation)();
                DictionaryPrefaceDFS(neighbor_index, visited, operation);
            }
            else
            {
                DictionaryPrefaceDFS(neighbor_index, visited);
            }
        }
    }
}

template<typename T>
void GraphWithoutDirection<T>::DictionaryPrefaceDFS(size_t start_index, vector<bool>& visited, void (GraphWithoutDirection<T>::*operation)(GraphNode<T>& node))
{
    sort(nodes[start_index].neighbors.begin(), nodes[start_index].neighbors.end());
    for (auto neighbor_index : nodes[start_index].neighbors)
    {
        if (!visited[neighbor_index])
        {
            visited[neighbor_index] = true;
            if (operation != nullptr)
            {
                (this->*operation)(nodes[neighbor_index]);
                DictionaryPrefaceDFS(neighbor_index, visited, operation);
            }
            else
            {
                DictionaryPrefaceDFS(neighbor_index, visited);
            }
        }
    }
}

template<typename T>
void GraphWithoutDirection<T>::BreadthFirstSearch(size_t start_index, vector<bool>& visited,  void (*operation)(GraphNode<T>& node))
{
    queue<size_t> list;
    list.push(start_index);
    while (!list.empty())
    {
        size_t index = list.front();
        list.pop();
        if (operation != nullptr)
        {
            operation(nodes[index]);
        }
        // sort(nodes[index].neighbors.begin(), nodes[index].neighbors.end());
        for (auto neighbor_index : nodes[index].neighbors)
        {
            if (!visited[neighbor_index])
            {
                visited[neighbor_index] = true;
                list.push(neighbor_index);
            }
        }
    }
}

template<typename T>
void GraphWithoutDirection<T>::BreadthFirstSearch(size_t start_index,vector<bool>& visited,  void (GraphWithoutDirection<T>::*operation)())
{
    queue<size_t> list;
    list.push(start_index);
    while (!list.empty())
    {
        size_t index = list.front();
        list.pop();
        if (operation != nullptr)
        {
            (this->*operation)();
        }
        // sort(nodes[index].neighbors.begin(), nodes[index].neighbors.end());
        for (auto neighbor_index : nodes[index].neighbors)
        {
            if (!visited[neighbor_index])
            {
                visited[neighbor_index] = true;
                list.push(neighbor_index);
            }
        }
    }
}

template<typename T>
void GraphWithoutDirection<T>::BreadthFirstSearch(size_t start_index, vector<bool>& visited,  void (GraphWithoutDirection<T>::* operation)(GraphNode<T>& node))
{
    
    queue<size_t> list;
    list.push(start_index);
    while (!list.empty())
    {
        size_t index = list.front();
        list.pop();
        if (operation != nullptr)
        {
            (this->*operation)(nodes[index]);
        }
            // sort(nodes[index].neighbors.begin(), nodes[index].neighbors.end());
        for (auto neighbor_index : nodes[index].neighbors)
        {
            if (!visited[neighbor_index])
            {
                visited[neighbor_index] = true;
                list.push(neighbor_index);
            }
        }
    }
}

template<typename T>
void GraphWithoutDirection<T>::DictionaryPrefaceBFS(size_t start_index, vector<bool>& visited,  void (*operation)(GraphNode<T>& node))
{
    queue<size_t> list;
    list.push(start_index);
    while (!list.empty())
    {
        size_t index = list.front();
        list.pop();
        if (operation != nullptr)
        {
            operation(nodes[index]);            
        }
        sort(nodes[index].neighbors.begin(), nodes[index].neighbors.end());
        for (auto neighbor_index : nodes[index].neighbors)
        {
            if (!visited[neighbor_index])
            {
                visited[neighbor_index] = true;
                list.push(neighbor_index);
            }
        }
    }
}

template<typename T>
void GraphWithoutDirection<T>::DictionaryPrefaceBFS(size_t start_index, vector<bool>& visited,  void (GraphWithoutDirection<T>::* operation)())
{
    queue<size_t> list;
    list.push(start_index);
    while (!list.empty())
    {
        size_t index = list.front();
        list.pop();
        if (operation != nullptr)
        {
            (this->*operation)();
        }
        sort(nodes[index].neighbors.begin(), nodes[index].neighbors.end());
        for (auto neighbor_index : nodes[index].neighbors)
        {
            if (!visited[neighbor_index])
            {
                visited[neighbor_index] = true;
                list.push(neighbor_index);
            }
        }
    }
}


template<typename T>
void GraphWithoutDirection<T>::DictionaryPrefaceBFS(size_t start_index, vector<bool>& visited,  void (GraphWithoutDirection<T>::* operation)(GraphNode<T>& node))
{
    queue<size_t> list;
    list.push(start_index);
    while (!list.empty())
    {
        size_t index = list.front();
        list.pop();
        if (operation != nullptr)
        {            
            (this->*operation)(nodes[index]);
        }
        sort(nodes[index].neighbors.begin(), nodes[index].neighbors.end());
        for (auto neighbor_index : nodes[index].neighbors)
        {
            if (!visited[neighbor_index])
            {
                visited[neighbor_index] = true;
                list.push(neighbor_index);
            }
        }
    }
}

template<typename T>
void GraphWithoutDirection<T>::DPDFSPrint(size_t start_index)
{
    // cout << "Dictionary Pre-Order DFS:" << endl;
    vector<bool> visited(nodes.size(), false);
    cout << start_index + 1 << " ";
    visited[start_index] = true;
    DictionaryPrefaceDFS(start_index, visited, printGraphNodeData);
    cout << endl;
}

template<typename T>
void GraphWithoutDirection<T>::DPBFSPrint(size_t start_index)
{
    // cout << "Dictionary Pre-Order BFS:" << endl;
    vector<bool> visited(nodes.size(), false);
    // cout << start_index + 1 << " ";
    // printGraphNode(nodes[start_index]);
    visited[start_index] = true;
    DictionaryPrefaceBFS(start_index, visited, printGraphNodeData);
    cout << endl;
}

template<typename T>
size_t GraphWithoutDirection<T>::BFSLength(size_t start_index)
{
    BFSCount = 0;
    vector<bool> visited(nodes.size(), false);
    visited[start_index] = true;
    BreadthFirstSearch(start_index, visited, &GraphWithoutDirection<T>::BFSCounter);
    return BFSCount;
}

template<typename T>
void GraphWithoutDirection<T>::BFSCounter()
{
    BFSCount++;
}

template<typename T>
size_t GraphWithoutDirection<T>::DFSLength(size_t start_index)
{
    DFSCount = 0;
    vector<bool> visited(nodes.size(), false);
    DepthFirstSearch(start_index, visited, &GraphWithoutDirection<T>::DFSCounter);
    return DFSCount;
}

template<typename T>
void GraphWithoutDirection<T>::DFSCounter()
{
    DFSCount++;
}

template<typename T>
int GraphWithoutDirection<T>::Dijkstra(size_t start_index, size_t end_index)
{
    //由于本题目的图是无权图，实际上使用Dijkstra算法与使用BFS算法的效果是一样的
    //但由于BFS算法的实现更简单，所以我们使用BFS算法来实现Dijkstra算法
    queue<size_t> list;
    vector<int> dist(nodes.size(), 2147483647);
    vector<bool> visited(nodes.size(), false);
    dist[start_index] = 0;
    list.push(start_index);
    while (!list.empty())
    {
        size_t index = list.front();
        list.pop();
        if (!visited[index])
        {
            visited[index] = true;
            for (auto neighbor_index : nodes[index].neighbors)
            {
                list.push(neighbor_index);
                dist[neighbor_index] = min(dist[neighbor_index], dist[index] + 1);            
            }
        }

    }
    if (dist[end_index] == 2147483647)
    {
        return -1;
    }
    return dist[end_index];
}


class Solution
{
public:
    void solve();
};

void Solution::solve()
{
    ios::sync_with_stdio(false);
    size_t n, m;
    cin >> n >> m;
    size_t start, end;
    cin >> start >> end;
    GraphWithoutDirection<int> graph(n);
    for (size_t i = 0; i < m; i++)
    {
        size_t op;
        cin >> op;
        if (op == 0)
        {
            size_t u, v;
            cin >> u >> v;
            graph.addEdge(u, v);
        }
        else if (op == 1)
        {
            size_t u, v;
            cin >> u >> v;
            graph.delEdge(u, v);
        }
    }
    graph.ConnectedComponents();
    graph.AllConnectivitySubgraphs();
    // cout << "DFS Length: " << graph.DFSLength(start - 1) << endl;
    // cout << "BFS Length: " << graph.BFSLength(end - 1) << endl;
    // graph.DPDFSPrint(start - 1);
    // graph.DPBFSPrint(end - 1);
    // cout << "Dijkstra: " << graph.Dijkstra(start - 1, end - 1) << endl;
    cout << graph.DFSLength(start - 1) << endl;
    graph.DPDFSPrint(start - 1);
    cout << graph.BFSLength(end - 1) << endl;
    graph.DPBFSPrint(end - 1);
    cout << graph.Dijkstra(start - 1, end - 1) << endl;
    // for (auto node : graph.getNodes())
    // {
    //     printGraphNode(node);
    // }
    return;
}

int main()
{
    Solution solution;
    solution.solve();
    return 0;
}