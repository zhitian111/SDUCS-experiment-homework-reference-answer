#include <iostream>
using namespace std;

int maxl(int A, int B) {
	return A > B ? A : B;
}

int maxl(int A, int B, int C) {
	return maxl(A, B) > maxl(B, C) ? maxl(A, B) : maxl(B, C);
}

double maxl(double A, double B) {
	return A > B ? A : B;
}

double maxl(double A, double B, double C) {
	return maxl(A, B) > maxl(B, C) ? maxl(A, B) : maxl(B, C);
}

int main() {
	int a, b, c, n;
	double x, y, z;
	cout << "ѡ��Ƚ�ģʽ1.��������2.��������3.����˫������4.����˫������" << endl;
	cin >> n;
	switch (n) {
		case 1:
			cin >> a >> b;
			cout << maxl(a, b);
			break;
		case 2:
			cin >> a >> b >> c;
			cout << maxl(a, b, c);
			break;
		case 3:
			cin >> x >> y;
			cout << maxl(x, y);
			break;
		case 4:
			cin >> x >> y >> z;
			cout << maxl(x, y, z);
			break;
		default:
			break;
	}
	return 0;
}