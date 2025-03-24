#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

bool check(int n) {
	for (int i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) {
			return 0;
		}
	}
	return 1;
}

int main() {
	int m, n;
	cin >> m >> n;
	float sum = 0;
	for (int i = m; i <= n; i++)
		sum += sqrt(1.0 * check(i) * i);
	cout << fixed << setprecision(2) << sum;
	return 0;
}