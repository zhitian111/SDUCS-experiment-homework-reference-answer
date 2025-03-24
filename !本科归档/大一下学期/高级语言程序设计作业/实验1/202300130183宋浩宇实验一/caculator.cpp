#include<iostream>
using namespace std;
int main() {
	float n, m;
	char a;
	cin >> n >> m >> a;
	switch (a)
	{
	case '+':
		cout << n << " + " << m << " = " << n + m;
		break;
	case '-':
		cout << n << " - " << m << " = " << n - m;
		break;
	case '*':
		cout << n << " * " << m << " = " << n * m;
		break;
	case '/':
		if (m == 0) {
			cout << "除数不能为0";
			break;
		}
		else {
			cout << n << " / " << m << " = " << n / m;
			break;
		}
	default:
		break;
	}
	return 0;
}