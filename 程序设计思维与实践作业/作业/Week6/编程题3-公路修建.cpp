#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

template<typename T>
class GraphNode
{
public:
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
class GraphWithDirection
{
private:
    vector<GraphNode<T>> nodes;
public:
    int ConnectedComponents();
    void DepthFirstSearch(size_t start_index, vector<bool>& visited, void (*operation)(GraphNode<T>& node) = nullptr);//调用类外函数
    void DepthFirstSearch(size_t start_index, vector<bool>& visited, void (GraphWithDirection<T>::* operation)(GraphNode<T>& node));//调用类内函数
    void DepthFirstSearch(size_t start_index, vector<bool>& visited, void (GraphWithDirection<T>::* operation)());//调用类内函数
    GraphWithDirection(size_t n);
    void addEdge(size_t u, size_t v);
    void delEdge(size_t u, size_t v);
};

template<typename T>
GraphWithDirection<T>::GraphWithDirection(size_t n)
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
void GraphWithDirection<T>::addEdge(size_t u, size_t v)
{
    nodes[u - 1].addNeighbor(v - 1);
    // nodes[v - 1].addNeighbor(u - 1);
}

template<typename T>
void GraphWithDirection<T>::delEdge(size_t u, size_t v)
{
    nodes[u - 1].delNeighbor(v - 1);
    // nodes[v - 1].delNeighbor(u - 1);
}


template<typename T>
int GraphWithDirection<T>::ConnectedComponents()
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
    // cout << count << endl;
    return count;
}

template<typename T>
void GraphWithDirection<T>::DepthFirstSearch(size_t start_index, vector<bool>& visited, void (*operation)(GraphNode<T>& node))
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
void GraphWithDirection<T>::DepthFirstSearch(size_t start_index, vector<bool>& visited, void (GraphWithDirection<T>::*operation)(GraphNode<T>& node))
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
void GraphWithDirection<T>::DepthFirstSearch(size_t start_index, vector<bool>& visited, void (GraphWithDirection<T>::*operation)())
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

void solve()
{
    int n;
    cin >> n;
    GraphWithDirection<int> graph(n);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        graph.addEdge(x, y);
        cout << "ANS: " << graph.ConnectedComponents() - 1 << endl;
    }
    cout << "Connected Components: " << graph.ConnectedComponents() << endl;
}

int main()
{
    solve();
    return 0;
}