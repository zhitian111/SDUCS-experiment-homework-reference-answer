/*2024数据结构--数据智能 实验4 链式描述线性表 B 链表合并.cpp*/
#include<iostream>
using namespace std;


template<class T>
void my_swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

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
class my_iterator
{
private:
    list_node<T>* current;
    unsigned int index;
public:
    my_iterator& operator++() { this->current = this->current->next; this->index++; return *this; };
    my_iterator& operator++(int) { my_iterator temp = *this; this->current = this->current->next;this->index++; return temp; };
    my_iterator& operator--() { this->current = this->current->front; this->index--; return *this; };
    my_iterator& operator--(int) { my_iterator temp = *this; this->current = this->current->front;this->index--; return temp; };
    bool operator==(const my_iterator& my_iterator) const { return this->current == my_iterator.current; };
    bool operator!=(const my_iterator& my_iterator) const { return this->current != my_iterator.current; };
    bool operator<(const my_iterator& my_iterator) const { return this->index < my_iterator.index; };
    my_iterator(list_node<T>* current, unsigned int index = 0) { this->current = current; this->index = index; };
    list_node<T>* getCurrent() { return this->current; };
    unsigned int getIndex() { return this->index; };
    void reset(list_node<T>* current) { this->current = current; this->index = 0; };
};

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
    void self_bubble_sort();
    void self_quick_sort();
    void print();
    list_node<T>* getNode(int index);
    list_node<T>* operator[](int index) { list_node<T>* temp = this->head; for (size_t i = 0; i < index; i++) { temp = temp->next; } return temp; };
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
    if (index == size)   
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

template<class T>
list_node<T>* chainlist<T>::getNode(int index)
{
    list_node<T>* temp = this->head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp;
}


template<class T>
void chainlist<T>::self_bubble_sort()
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size - i - 1; j++)
        {
            if (getNode(j)->getData() > getNode(j + 1)->getData())
            {
                my_swap(getNode(j)->getData(), getNode(j + 1)->getData());
            }
        }
        
    }
    
}

template<class T>
void quick_sort(my_iterator<T> head, my_iterator<T> tail)
{
    if (head == tail||tail<head) { return; }
    T pivot = head.getCurrent()->getData();
    my_iterator<T> i = head;
    my_iterator<T> j = tail;
    while (i < j)
    {
        while (j.getCurrent()->getData() >= pivot && i < j)
        {
            j--;
        }
        if (i<j)
        {
            i.getCurrent()->getData() = j.getCurrent()->getData();
        }
        
        while (i.getCurrent()->getData() <= pivot && i < j)
        {
            i++;
        }
        if (i<j)
        {
            j.getCurrent()->getData() = i.getCurrent()->getData();
        }        
        if (i==j)
        {
            i.getCurrent()->getData() = pivot;
        }
    }
    my_iterator<T> j2 = j;
    j2++;
    quick_sort(head, j);
    quick_sort(j2, tail);
}

template<class T>
void chainlist<T>::self_quick_sort()
{
    my_iterator<T> head(this->head);
    my_iterator<T> tail(this->back, this->size - 1);
    quick_sort(head, tail);
}

class Solution {

public:
    void solute();
    void test();
};

void Solution::solute()
{
    chainlist<int> list1;
    chainlist<int> list2;
    int a, b;
    cin >> a >> b;
    for (size_t i = 0; i < a; i++)
    {
        int value;
        cin >> value;
        list1.push_back(value);
    }
    for (size_t i = 0; i < b; i++)
    {
        int value;
        cin >> value;
        list2.push_back(value);
    }
    chainlist<int> list3;
    my_iterator<int> it2(list2.getHead());
    my_iterator<int> it1(list1.getHead());
    my_iterator<int> it3(list3.getHead());
    while (it1.getCurrent() != nullptr)
    {
        list3.push_back(it1.getCurrent()->getData());
        it1++;
    }
    while (it2.getCurrent() != nullptr)
    {
        list3.push_back(it2.getCurrent()->getData());
        it2++;
    }
    list1.self_quick_sort();
    list2.self_quick_sort();
    list3.self_quick_sort();
    it1.reset(list1.getHead());
    it2.reset(list2.getHead());
    it3.reset(list3.getHead());
    int ans1 = 0, ans2 = 0, ans3 = 0;
    while (it1.getCurrent() != nullptr)
    {
        ans1 += it1.getCurrent()->getData() ^ it1.getIndex();
        it1++;
    }
    while (it2.getCurrent() != nullptr)
    {
        ans2 += it2.getCurrent()->getData() ^ it2.getIndex();
        it2++;
    }
    while (it3.getCurrent() != nullptr)
    {
        ans3 += it3.getCurrent()->getData() ^ it3.getIndex();
        it3++;
    }
    cout << ans1 << endl << ans2 << endl << ans3;
}

void Solution::test()
{
    chainlist<int> list1;
    int n;
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        int value;
        cin >> value;
        list1.push_back(value);
    }
    list1.print();
    my_iterator<int> it1(list1.getHead());
    my_iterator<int> it2(list1.getBack(), list1.getSize() - 1);
    
    quick_sort(it1, it2);
    list1.print();
}

int main()
{
    
    Solution solution;
    
    solution.solute();

    return 0;

}
