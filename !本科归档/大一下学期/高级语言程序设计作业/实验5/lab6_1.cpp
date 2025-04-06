#include<iostream>
using namespace std;
int main() {
	int n[3][3];
	int ans[3][3];
	cout << "输入一个3×3矩阵：" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> n[i][j];
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ans[i][j] = n[j][i];
		}
	}
	cout << "原矩阵的转置为：" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}