#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int n = 0, right_digit;
	string a;
	cout << "Enter the number:" << endl;
loop:
	cin >> a;
	for (int i = 0; i < a.length(); i++) {
		if (a[i] > '9' || a[i] < '0') {
			cout << "Please enter \"number\"" << endl;
			goto loop;
		}
	}
	for (int i = 0; i < a.length(); i++) {
		n += (a[i] - '0') * pow(10, a.length() - i - 1);
	}
	cout << "The number in reverse order is ";
	do {
		right_digit = n % 10;
		cout << right_digit;
		n /= 10;
	} while (n != 0);
	cout << endl;
	return 0;
}