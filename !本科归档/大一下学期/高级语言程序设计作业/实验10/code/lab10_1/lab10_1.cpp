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
	cout << "原本的A链" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << endl;
	}
	cout << "原本的B链" << endl;
	for (int i = 0; i < b.size(); i++)
	{
		cout << b[i] << endl;
	}
	a.insert(a.end(), b.begin(), b.end());
	cout << "链接后的A链" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << endl;
	}
	return 0;
}
