#include <iostream>
using namespace std;

int rabbits(int a) {
	if (a == 1 || a == 2) {
		return 1;
	}
	return rabbits(a - 1) + rabbits(a - 2);
}

int main() {
	int n;
	cin >> n;
	cout << "��" << n << "����" << rabbits(n) << "ֻĸ��";
	return 0;
}