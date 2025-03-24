#include<iostream>
using namespace std;
int main() {
	int (*p)[3] = new int[3][3];
	cout << "输入一个3×3的矩阵：" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> *(*(p + i) + j);
		}
	}
	int(*ans)[3] = new int[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			*(*(ans + i) + j) = *(*(p + j) + i);
		}
	}
	cout << "原矩阵的转置为：" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << *(*(ans + i) + j) << " ";
		}
		cout << endl;
	}
	return 0;
}