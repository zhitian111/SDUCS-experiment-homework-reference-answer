#include<iostream>
using namespace std;
int dp[10000];
int fib(int n);
int main() {
	int a;
	cin >> a;
	cout << fib(a);
	return 0;
}
int fib(int n){
	if (n == 1) {
		dp[1] = 1;
		return 1;
	}
	if (n == 2) {
		dp[2] = 1;
		return 1;
	}
	if (dp[n]) {
		return dp[n];
	}
	else {
		dp[n] = fib(n - 1) + fib(n - 2);
		return dp[n];
	}
}