#include<iostream>
using namespace std;




int main() {
	char a[100], b[100],c[100];
	cout << "�����ַ�����" << endl;
	cin >> a >> b;
	for (int i = 0; i < strlen(a); i++) {
		c[i] = a[i];
	}
	for (int i = 0; i < strlen(b); i++) {
		c[i + strlen(a)] = b[i];
	}
	c[strlen(a) + strlen(b) + 1] = '\0';
	cout << "����֮����ַ���Ϊ��" << c << endl;
	return 0;
}