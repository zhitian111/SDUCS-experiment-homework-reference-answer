#include<iostream>
using namespace std;
int main() {
	int n[3][3];
	int ans[3][3];
	cout << "����һ��3��3����" << endl;
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
	cout << "ԭ�����ת��Ϊ��" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}