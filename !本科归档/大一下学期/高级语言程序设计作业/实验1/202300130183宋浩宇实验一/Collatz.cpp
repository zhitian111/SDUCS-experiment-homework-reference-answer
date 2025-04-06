
#include <iostream>
using namespace std;


int main() {
	int n;
	cin >> n;
	while (n > 1) {
		if (n % 2) {
			cout << n << " * 3 + 1 = " << n * 3 + 1 << endl;
			n *= 3;
			n++;
		} else {
			cout << n << " / 2 = " << n / 2 << endl;
			n /= 2;
		}
	}
	cout << "End" << endl;
	return 0;
}
