

#include<iostream>
using namespace std;

template<class T>
bool CheckIn(T target, T container[], unsigned long long n)
{
	if (n == 1) return container[n - 1] == target;
	return (container[n - 1] == target) || CheckIn(target, container, n - 1);
}


int main()
{
	int a[5] = { 1,2,3,4,5 };
	cout << CheckIn(0, a, 5);
}

