/*2024级数据结构--数据智能 实验7 队列 A 卡片游戏 数组描述.cpp*/
#include <iostream>

using namespace std;

template<class T>
class queue
{
private:
    T* data;
    int front; //当前的头
    int tile;  //当前的最后一个的下一个
    int capacity;
public:
    queue(int capacity) {
        this->capacity = capacity;
        data = new T[capacity];
        front = 0;
        tile = 0;
    }
    ~queue() {
        delete[] data;
    }
    void push(T&& a_data) {
        if (tile == capacity) {
            T* newData = new T[capacity * 2];
            
            for (int i = front; i < tile; i++) {
                newData[i - front] = this->data[i];
            }
            delete[] data;
            tile -= front;
            data = newData;
            front = 0;
            capacity *= 2;
        }
        data[tile++] = a_data;
    }
    void push(T& a_data)
    {
        if (tile == capacity) {
        T* newData = new T[capacity * 2];
           
        for (int i = front; i < tile; i++) {
            newData[i - front] = this->data[i];
        }
        delete[] data;
        tile -= front;
        data = newData;
        front = 0;
        capacity *= 2;
    }
        data[tile++] = a_data;
    }
    T pop() {
        return data[front++];
    }
    
    int size() {
        return tile - front;
    }
};


class Solution
{
public:
    void solve();
};



void Solution::solve()
{
    queue<int> q(1000);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        q.push(i + 1);
    }
    while (q.size() > 1) {
        q.pop();
        q.push(q.pop());
    }
    cout << q.pop();
}


int main()
{
    Solution s;
    s.solve();
    return 0;
}