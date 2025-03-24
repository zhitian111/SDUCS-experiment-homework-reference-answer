#include<iostream>
using namespace std;

int fun(int a)
{
	a = 3; 
	cout << a << endl;
	return 1;
}

int main()
{
	int a = 1;
	cout << a << endl;
	fun(a); 
	cout << a << endl;
	return 0;
}