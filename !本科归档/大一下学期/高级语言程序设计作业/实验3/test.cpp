#include <iostream>
using namespace std;

class CPU {
	private:
		int a: 32;
		int b: 1;
		int c: 2;
		int d: 1;
};

int main() {
	CPU cpu;
	cout << sizeof(cpu);
}