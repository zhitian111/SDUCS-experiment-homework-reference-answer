#include<iostream>

using namespace std;

int main() {
	float y = 2.0;
	while (y >= -2.0) {
		float x = -2.0;
		while (x < 2.0) {
			float a = x * x + y * y - 1;
			if (a * a * a - x * x * y * y * y <= 0.0) {
				cout << '*';
			}
			else {
				cout << ' ';
			}
			x += 0.05;
		}
		y -= 0.1;
		cout << endl;
	}

	return 0;
}
