#include <iostream>
using namespace std;

int main() {
	int a = 10;
	const int *p = &a;
	p = new int(5);
	//int *q = p;
	cout << *p;
	return 0;
}