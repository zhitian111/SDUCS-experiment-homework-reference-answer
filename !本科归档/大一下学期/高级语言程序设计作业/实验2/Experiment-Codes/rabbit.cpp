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
	cout << "第" << n << "年有" << rabbits(n) << "只母兔";
	return 0;
}