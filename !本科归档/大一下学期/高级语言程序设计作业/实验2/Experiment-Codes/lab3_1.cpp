#include<iostream>
using namespace std;


float Convert(float TempFer) {
	return (TempFer - 32) * 5 / 9;
}

int main() {
	float C;
	cin >> C;
	cout << Convert(C);
	return 0;
}