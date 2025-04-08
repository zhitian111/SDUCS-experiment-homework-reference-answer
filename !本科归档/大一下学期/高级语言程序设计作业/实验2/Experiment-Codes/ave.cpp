#include <iostream>
#include <iomanip>
using namespace std;

int check(int n) {
	if (n > 0) {
		return 1;
	}
	if (n == 0) {
		return 0;
	}
	if (n < 0) {
		return -1;
	}
}

int main() {
	int n;
	int sum = 0, cnt = 0;;
	cin >> n;
	int a;
	for (int i = 0; i < n; i++) {
		cin >> a;
		if (check(a) == 1) {
			cnt++;
			sum += a;
		}
	}
	cout << fixed << setprecision(2) << (sum * 1.0 / cnt * 1.0);
	return 0;
}