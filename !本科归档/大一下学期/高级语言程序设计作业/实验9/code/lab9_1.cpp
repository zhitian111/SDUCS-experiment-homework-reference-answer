#include"Node.h"
#include<iostream>
using namespace std;
//�������
//��
template<typename T>
void NodeAdd(Node<T>* head,T data)
{
	while (head->nextNode() != NULL)
	{
		head = head->nextNode();
	}
	Node<T>* p =new Node<T>(data,NULL);
	head->insertAfter(p);
	cout << "������ĩ��������" << p->data << endl;
}
//ɾ
template<typename T>
void NodeDelete(Node<T>* head, T data)
{
	if (head->data == data)
	{
		head->data = head->nextNode()->data;
		head->deleteAfter();
		cout << "��ɾ��" << data << endl;
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
			cout << "��ɾ��" << data << endl;
			return;
		}
		head = head->nextNode();
	}
	cout << "δ�ҵ���Ҫɾ����Ԫ��" << endl;
}
//��
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
//��
template<typename T>
void NodeChange(Node<T>* head, T data, T to)
{
	if (head->data == data)
	{
		head->data = to;
		cout << "�ѽ�" << data << "��Ϊ" << to << endl;
		return;
	}
	while (head->nextNode() != NULL)
	{
		head = head->nextNode();
		if (head->data == data)
		{
			head->data = to;
			cout << "�ѽ�" << data << "��Ϊ" << to << endl;
			return;
		}
	}
	cout << data << "����������" << endl;
}
//���
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
		cout << "2��������" << endl;
	}
	if (!NodeCheck(&test, 1))
	{
		cout << "1����������" << endl;
	}
	Print(&test);

	NodeChange(&test, 2, 1);
	Print(&test);
	NodeChange(&test, 2, 1);
	Print(&test);

	return 0;
}

