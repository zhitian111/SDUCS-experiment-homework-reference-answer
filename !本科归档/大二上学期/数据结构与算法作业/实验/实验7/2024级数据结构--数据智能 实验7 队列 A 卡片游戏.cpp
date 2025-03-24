/*2024级数据结构--数据智能 实验7 队列 A 卡片游戏.cpp*/
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
class queue
{
private:
    list_node<T>* head;
    list_node<T>* tail;
    int count;
public:
    queue() { head = nullptr; tail = nullptr;count = 0; };
    bool empty() { return count == 0; };
    void push(T& data);
    void push(T&& data);
    void push(list_node<T>& data);
    void pop_free();
    T& pop();
    T& front();
    list_node<T>& pop_node();
    void print();
    int size() { return count; };
};

template<class T>
void queue<T>::push(T&& data)
{
    list_node<T>* new_node = new list_node<T>(data);
    if (empty()) {
        head = new_node;
        tail = new_node;
    }
    else
    {
        tail->next = new_node;
        tail = new_node;
    }
    count++;
}

template<class T>
list_node<T>& queue<T>::pop_node()
{
    if (empty())
    {
        return *(new list_node<T>());
    }
    else
    {
        count--;
        list_node<T>& data = *head;
        head = head->getNext();
        return data;
    }
}

template<class T>
void queue<T>::push(T& data)
{
    list_node<T>* new_node = new list_node<T>(data);
    if (empty()) {
        head = new_node;
        tail = new_node;
    }
    else
    {
        tail->next = new_node;
        tail = new_node;
    }
    count++;
}

template<class T>
void queue<T>::push(list_node<T>& data)
{
    if (empty()) {
        head = &data;
        tail = &data;
    }
    else
    {
        tail->next = &data;
        tail = &data;
    }
    count++;
}

template<class T>
T& queue<T>::pop()
{
    if (empty())
    {
        return *(new T(0));
    }
    else
    {
        count--;
        T& data = head->getData();
        head = head->getNext();
        return data;
    }
}


template<class T>
void queue<T>::print()
{
    list_node<T>* temp = head;
    while (temp!= nullptr)
    {
        cout << temp->getData() << " ";
        temp = temp->getNext();
    }
    cout << endl;
}
template<class T>
void queue<T>::pop_free()
{
    if (empty())
    {
        return;
    }
    else
    {
        count--;
        list_node<T>* temp = head;
        head = head->getNext();
        // temp.~list_node<T>();
        delete temp;
    }
}

template<class T>
T& queue<T>::front()
{
    if (empty())
    {
        return *(new T(0));

    }
    else
    {
        return head->getData();
    }
}

class Solution
{
public:
    void solve();
};

void Solution::solve()
{
    queue<int> q;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        q.push(i + 1);
    }
    while (q.size() > 1)
    {
        q.pop_free();
        // int temp = q.pop();
        // q.push(temp);
        q.push(q.pop_node());
    }
    cout << q.front();
}


int main()
{
    Solution solution;
    solution.solve();
    return 0;
}