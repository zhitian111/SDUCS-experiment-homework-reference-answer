#include<iostream>
#include<vector>
using namespace std;
//已将queue.h文件中应有的内容移动到此处
template<class T>
class Queue
{
private:
	vector<T> datas;
	int size = 0;
public:
	void insert(T data);
	T get();
};

template<class T>
void Queue<T>::insert(T data)
{
	datas.push_back(data);
	size++;
}

template<class T>
T Queue<T>::get()
{
	T tem = datas[--size];
	datas.pop_back();
	return tem;
}

int main()
{
	Queue<int> queue;
	queue.insert(1);
	queue.insert(2);
	queue.insert(3);
	queue.insert(4);
	queue.insert(5);
	for (int i = 0; i < 5; i++)
	{
		cout << queue.get() << endl;
	}
	return 0;
}