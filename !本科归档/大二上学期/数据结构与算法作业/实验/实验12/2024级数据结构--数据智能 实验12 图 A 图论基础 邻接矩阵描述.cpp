﻿/*2024级数据结构--数据智能 实验12 图 A 图论基础 邻接矩阵描述.cpp*/
#include <iostream>
using namespace std;


template<class T>
class list_node
{
private:
    T data;

public:
    list_node<T>* front;
    list_node<T>* next;
    bool operator==(const list_node<T>& list_node) const { return this->data == list_node.data; };
    T& getData() { return data; };
    list_node<T>* getFront() { return front; };
    list_node<T>* getNext() { return next; };
    list_node(){};
    list_node(const T& data, list_node<T>* front = nullptr, list_node<T>* next = nullptr);
    list_node(list_node<T>* const list_node) { this->data = list_node->data;this->front = list_node->front;this->next = list_node->next; };
};

template<class T>
list_node<T>::list_node(const T& data,list_node<T>* front,list_node<T>* next)
:data(data),front(front),next(next)
{

}

template<class T>
class chainlist
{
private:
    list_node<T>* head;
    list_node<T>* back;
    unsigned int size;
public:
    void push_back(list_node<T>* operated_list_node);
    void push_back(const T& data);
    void push_front(list_node<T>* operated_list_node);
    void push_front(const T& data);
    void pop_back();
    void pop_front();
    void insert(T data, int index);
    void insert(list_node<T>* operated_list_node, int index);
    void erase(const unsigned int index);
    unsigned int getSize() { return size; };
    unsigned int find_first(list_node<T>* operated_list_node);
    unsigned int find_first(const T& data);
    void inverse();
    chainlist();
    chainlist(const chainlist<T>& chainlist);
    void print();
    list_node<T>* getHead() { return head; };
    list_node<T>* getBack() { return back; };
    
};

template<class T>
void chainlist<T>::push_back(list_node<T>* operated_list_node)
{
    list_node<T>* new_list_node = new list_node<T>(operated_list_node);

    
    if (size == 0)
    {
        this->head = new_list_node;
        this->back = new_list_node;
        size++;        
        return;
    }

    this->back->next = new_list_node;
    new_list_node->front = this->back;
    new_list_node->next = nullptr;
    this->back = new_list_node;

    size++;
}

template<class T>
void chainlist<T>::push_back(const T& data)
{
    T new_data = data;
    list_node<T>* new_list_node = new list_node<T>(new_data);
    this->push_back(new_list_node);
    delete new_list_node;
}

template<class T>
void chainlist<T>::push_front(list_node<T>* operated_list_node)
{
    list_node<T>* new_list_node = new list_node<T>(operated_list_node);

    if (size == 0)
    {
        this->back = new_list_node;
        this->head = new_list_node;
        size++;
        return;
    }
    new_list_node->next = this->head;
    new_list_node->front = nullptr;
    this->head->front = new_list_node;
    this->head = new_list_node;

    size++;
}

template<class T>
void chainlist<T>::push_front(const T& data)
{
    T new_data = data;
    list_node<T>* new_list_node = new list_node<T>(new_data);
    this->push_front(new_list_node);
    delete new_list_node;
}

template<class T>
void chainlist<T>::pop_back()
{
    if (this->back == nullptr) return;
    list_node<T>* temp = this->back;
    this->back = this->back->front;
    delete temp;
    if (size == 1)
    {
        this->head = nullptr;
        this->back = nullptr;
    }
    
    size--;
}

template<class T>
void chainlist<T>::pop_front()
{
    if (this->head == nullptr) return;
    list_node<T>* temp = this->head;
    this->head = this->head->next;
    delete temp;
    if (size == 1)
    {
        this->head = nullptr;
        this->back = nullptr;
    }
    size--;
}


template<class T>
void chainlist<T>::insert(list_node<T>* operated_list_node, int index)
{
    if (index == 0)
    {
        push_front(operated_list_node);
        return;
    }
    if (index == size)   
    {
        push_back(operated_list_node);
        return;
    }
    
    list_node<T>* temp = this->head;
    for (int i = 0; i < index - 1; i++)
    {
        temp = temp->next;
    }
    list_node<T>* new_list_node = new list_node<T>(operated_list_node);
    new_list_node->next = temp->next;
    temp->next->front = new_list_node;
    temp->next = new_list_node;
    new_list_node->front = temp;
    size++;
}

template<class T>
void chainlist<T>::insert(T data, int index)
{
    list_node<T>* new_list_node = new list_node<T>(data);
    this->insert(new_list_node, index);
    delete new_list_node;

}

template<class T>
void chainlist<T>::erase(const unsigned int index)
{
    if (index == 0)   
    {
        pop_front();
        return;
    }
    if (index == size - 1)   
    {
        pop_back();
        return;
    }
    
    list_node<T>* temp = this->head;
    for (int i = 0; i < index - 1; i++)
    {
        temp = temp->next;
    }
    list_node<T>* temp2 = temp->next;
    temp->next = temp2->next;
    temp->next->front = temp;
    delete temp2;
    size--;
}

template<class T>
unsigned int chainlist<T>::find_first(list_node<T>* operated_list_node)
{
    list_node<T>* temp = this->head;
    unsigned int index = 0;
    while (temp != nullptr)
    {
        if ((*temp) == (*operated_list_node)) return index;
        temp = temp->next;
        index++;
    }
    return -1;
}

template<class T>
unsigned int chainlist<T>::find_first(const T& data)
{
    list_node<T>* temp = this->head;
    unsigned int index = 0;
    while (temp != nullptr)
    {
        if (temp->getData() == data) return index;
        temp = temp->next;
        index++;
    }
    return -1;
}

template<class T>
void chainlist<T>::inverse()
{
    list_node<T>* temp1 = this->head;
    list_node<T>* temp2 = nullptr;
    list_node<T>* temp3 = nullptr;
    for (int i = 0; i < size; i++)
    {
        temp2 = temp1->next;
        temp3 = temp1->front;
        temp1->front = temp1->next;
        temp1->next = temp3;
        temp1 = temp2;
    }
    temp1 = this->head;
    this->head = this->back;
    this->back = temp1;
}

template<class T>
chainlist<T>::chainlist()
{
    this->head = nullptr;
    this->back = nullptr;
    this->size = 0;
}

template<class T>
chainlist<T>::chainlist(const chainlist<T>& chainlist)
{
    this->head = nullptr;
    this->back = nullptr;
    this->size = 0;
    list_node<T>* temp = chainlist.head;
    while (temp != nullptr)
    {
        push_back(temp);
        temp = temp->next;       
    }
}

template<class T>
void chainlist<T>::print()
{
    list_node<T>* temp = this->head;
    while (temp != nullptr)
    {
        cout << temp->getData() << " ";
        temp = temp->next;
    }
    cout << endl;
}

template <typename T>
struct GraphNode
{
    T data; // 节点数据
    chainlist<GraphNode<T>*> neighbors; // 邻接表
};

template <typename T>
class GraphWithoutDirection
{
private:
    size_t n; // 图的顶点数
    size_t e; // 图的边数
    GraphNode<T>* nodes; // 图的节点数组
public:
    GraphWithoutDirection(size_t n);
    void addEdge(size_t u, size_t v);
    void delEdge(size_t u, size_t v);
    void print();
};

template <typename T>
GraphWithoutDirection<T>::GraphWithoutDirection(size_t n)
{
    this->n = n;
    this->e = 0;
    this->nodes = new GraphNode<T>[n];
    for (size_t i = 0; i < n; i++)
    {
        this->nodes[i].data = i;
    }
}

template <typename T>
void GraphWithoutDirection<T>::addEdge(size_t u, size_t v)
{
    this->nodes[u].neighbors.push_back(&this->nodes[v]);
    this->nodes[v].neighbors.push_back(&this->nodes[u]);
    this->e++;
}
template <typename T>
void GraphWithoutDirection<T>::delEdge(size_t u, size_t v)
{
    this->nodes[u].neighbors.erase(this->nodes[u].neighbors.find_first(&this->nodes[v]));
    this->nodes[v].neighbors.erase(this->nodes[v].neighbors.find_first(&this->nodes[u]));
    this->e--;
}

template <typename T>
void GraphWithoutDirection<T>::print()
{
    for (size_t i = 0; i < this->n; i++)
    {
        cout << i << " : ";
        for (list_node<GraphNode<T>*>* neighbor = this->nodes[i].neighbors.getHead(); neighbor != nullptr; neighbor = neighbor->next)
        {
            cout << neighbor->getData()->data << " ";
        }
        cout << endl;
    }
}

class Solution
{
public:
    void solve();
};

void Solution::solve()
{
    GraphWithoutDirection<int> graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.print();
}

int main()
{
    Solution solution;
    solution.solve();
    return 0;
}