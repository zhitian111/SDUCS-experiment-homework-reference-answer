#include<iostream>
#include<deque>
using namespace std;
int main()
{
	deque<int> a;
	deque<int> b;
	for (int i = 0; i < 5; i++)
	{
		a.push_back(i);
		b.push_back(i);
	}
	cout << "ԭ����A��" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << endl;
	}
	cout << "ԭ����B��" << endl;
	for (int i = 0; i < b.size(); i++)
	{
		cout << b[i] << endl;
	}
	a.insert(a.end(), b.begin(), b.end());
	cout << "���Ӻ��A��" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << endl;
	}
	return 0;
}
