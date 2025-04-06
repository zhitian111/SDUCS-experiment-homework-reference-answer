#include"Node.h"
#include<iostream>
using namespace std;
//链表操作
//增
template<typename T>
void NodeAdd(Node<T>* head,T data)
{
	while (head->nextNode() != NULL)
	{
		head = head->nextNode();
	}
	Node<T>* p =new Node<T>(data,NULL);
	head->insertAfter(p);
	cout << "在链表末端增加了" << p->data << endl;
}
//删
template<typename T>
void NodeDelete(Node<T>* head, T data)
{
	if (head->data == data)
	{
		head->data = head->nextNode()->data;
		head->deleteAfter();
		cout << "已删除" << data << endl;
		return;
	}
	if (head->nextNode()->data == data)
	{
		head->deleteAfter();
		return;
	}
	while (head->nextNode()->nextNode() != NULL)
	{
		if (head->nextNode()->data == data)
		{
			head->deleteAfter();
			cout << "已删除" << data << endl;
			return;
		}
		head = head->nextNode();
	}
	cout << "未找到需要删除的元素" << endl;
}
//查
template<typename T>
bool NodeCheck(Node<T>* head, T data)
{
	if (head->data == data)
	{
		return true;
	}
	while (head->nextNode()!=NULL)
	{
		head = head->nextNode();
		if (head->data == data)
		{
			return true;
		}
	}
	return false;
}
//改
template<typename T>
void NodeChange(Node<T>* head, T data, T to)
{
	if (head->data == data)
	{
		head->data = to;
		cout << "已将" << data << "改为" << to << endl;
		return;
	}
	while (head->nextNode() != NULL)
	{
		head = head->nextNode();
		if (head->data == data)
		{
			head->data = to;
			cout << "已将" << data << "改为" << to << endl;
			return;
		}
	}
	cout << data << "不在链表中" << endl;
}
//输出
template<typename T>
void Print(Node<T>* head)
{
	cout << head->data << endl;
	while (head->nextNode() != NULL)
	{
		head = head->nextNode();
		cout << head->data << endl;
	}
}
int main()
{
	Node<int> test(0,NULL);
	NodeAdd(&test, 1);
	NodeAdd(&test, 2);
	NodeAdd(&test, 3);

	Print(&test);
	NodeDelete(&test, 1);
	Print(&test);
	if (NodeCheck(&test, 2))
	{
		cout << "2在链表中" << endl;
	}
	if (!NodeCheck(&test, 1))
	{
		cout << "1不在链表中" << endl;
	}
	Print(&test);

	NodeChange(&test, 2, 1);
	Print(&test);
	NodeChange(&test, 2, 1);
	Print(&test);

	return 0;
}

