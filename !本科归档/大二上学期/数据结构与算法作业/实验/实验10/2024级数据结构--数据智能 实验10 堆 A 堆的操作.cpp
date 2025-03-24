/*2024级数据结构--数据智能 实验10 堆 A 堆的操作.cpp*/
#include <iostream>

using namespace std;

template<class T>
struct Node
{
    T data;
    Node<T>* left, * right, * parent;
    size_t depth;
    size_t sons;
    bool touched;
    Node(Node<T>* parent, const T& data) : data(data), left(nullptr), right(nullptr), parent(parent), depth(0), sons(0), touched(false) {}
    Node(): left(nullptr), right(nullptr), parent(nullptr), depth(0), sons(0), touched(false) {}
};


template <typename T>
class Heap
{
protected:
    Node<T>** data;
    size_t count;
    size_t capacity;
public:
    Heap(size_t capacity);
    ~Heap();
    virtual void push(const T& value) = 0;
    virtual T pop() = 0;
    T& top();
    bool empty() const;
    size_t size() const;
    void print() const;
};

template <typename T>
Heap<T>::Heap(size_t capacity)
{
    this->capacity = capacity;
    this->count = 0;
    this->data = new Node<T>*[capacity];
}

template <typename T>
Heap<T>::~Heap()
{
    delete[] data;
}

template <typename T>
T& Heap<T>::top()
{
    if (empty())
    {
        return *(new T(0));
    }
    else
    {
        return (*data[0]).data;
    }
}

template <typename T>
bool Heap<T>::empty() const
{
    return count == 0;
}


template <typename T>
size_t Heap<T>::size() const
{
    return count;
}

template <typename T>
void Heap<T>::print() const
{
    for (size_t i = 0; i < count; i++)
    {
        cout << (*data[i]).data << " ";
    }
    cout << endl;
}


template <typename T>
class minHeap : public Heap<T>
{
public:
    minHeap(size_t capacity) : Heap<T>(capacity) {}
    virtual void push(const T& value) final override;
    virtual T pop() final override;
};

template <typename T>
void minHeap<T>::push(const T& value)
{
    if (this->data == nullptr)
    {
        this->data = new Node<T>*[this->capacity];
    }
    if (this->count == this->capacity)
    {
        Node<T>** temp = new Node<T>*[this->capacity * 2];
        for (size_t i = 0; i < this->capacity; i++)
        {
            temp[i] = this->data[i];
        }
        delete[] this->data;
        this->data = temp;
        this->capacity *= 2;
    }
    if (this->count == 0)
    {
        this->data[0] = new Node<T>(nullptr, value);
        this->count++;
    }
    else
    {
        Node<T>* temp = new Node<T>(this->data[int(this->count - 1) / 2], value);
        this->data[this->count] = temp;
        this->count++;
        if (this->count % 2 == 0)
        {
            temp->parent->left = temp;
        }
        else
        {
            temp->parent->right = temp;
        }
        while (temp != nullptr && temp->parent != nullptr && temp->data < temp->parent->data)
        {
            swap(temp->data, temp->parent->data);
            temp = temp->parent;
        }
    }
}

template <typename T>
T minHeap<T>::pop()
{
    if (this->count == 0)
    {
        return *(new T());
    }
    T value = this->data[0]->data;
    this->count--;
    if (this->count == 0)
    {
        return value;
    }
    else
    {
        swap(this->data[0]->data, this->data[this->count]->data);
        if (this->count % 2 == 0)
        {
            this->data[this->count] -> parent -> right = nullptr;
        }
        else
        {
            this->data[this->count] -> parent -> left = nullptr;
        }
        delete this->data[this->count];
        this->data[this->count] = nullptr;
        Node<T>* temp = this->data[0];

        while (1)
        {
            if (temp->left != nullptr && temp->right != nullptr && temp->left->data <= temp->right->data && temp->left->data < temp->data)
            {
                swap(temp->data, temp->left->data);

                temp = temp->left;
            }
            else if (temp->right != nullptr && temp -> right != nullptr && temp->right->data < temp->left->data && temp->right->data < temp->data)
            {
                swap(temp->data, temp->right->data);

                temp = temp->right;
            }
            else if (temp->left != nullptr && temp->right == nullptr && temp->left->data < temp->data)
            {
                swap(temp->data, temp->left->data);

                temp = temp->left;
            }
            else if (temp->right != nullptr && temp->left == nullptr && temp->right->data < temp->data)
            {
                swap(temp->data, temp->right->data);

                temp = temp->right;
            }
            else
            {
                break;
            }
        }
    }
    // this->print();
    return value;
}


class Solution
{
public:
    void solve();
};

void Solution::solve()
{
    size_t n;
    cin >> n;
    minHeap<int> heap(n);
    for (size_t i = 0; i < n; i++)
    {
        size_t x;
        cin >> x;
        heap.push(x);
    }
    cout << heap.top() << endl;
    size_t m;
    cin >> m;
    for (size_t i = 0; i < m; i++)
    {
        size_t operation;
        cin >> operation;
        if (operation == 1)
        {
            size_t x;
            cin >> x;
            heap.push(x);
            cout << heap.top() << endl;
        }
        
        else if (operation == 2)
        {
            heap.pop();
            cout << heap.top() << endl;
        }
        else if (operation == 3)
        {
            size_t cnt;
            cin >> cnt;
            minHeap<int> sort_heap(cnt);
            for (size_t j = 0; j < cnt; j++)
            {
                size_t x;
                cin >> x;
                sort_heap.push(x);
            }
            for (size_t j = 0; j < cnt; j++)
            {
                cout << sort_heap.pop() << " ";
            }
        }
    }
}

int main()
{
    Solution solution;
    solution.solve();
    return 0;
}