#include <iostream>
#include <vector>
// 并查集类 
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
    size_t n, m;
    std::cin >> n >> m;
    UnionFindSet<int> ufs(n);
    for (size_t i = 0; i < m; i++)
    {
        int a, b;
        std::cin >> a >> b;
        ufs.merge(a - 1, b - 1);
        std::cout << ufs.type_cnt - 1 << std::endl;
    }
}

int main()
{
    solve();
    return 0;
}