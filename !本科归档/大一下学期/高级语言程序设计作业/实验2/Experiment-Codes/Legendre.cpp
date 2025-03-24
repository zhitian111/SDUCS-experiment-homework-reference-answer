#include <iostream>
using namespace std;

int x;

long long P(int n) {
	if (n == 0)
		return 1;
	if (n == 1)
		return x;
	return ((2 * n - 1) * x * P(n - 1) - (n - 1) * P(n - 2)) / n;
}

int main() {
	int n;
	cin >> x >> n;
	cout << P(n);
	return 0;
}