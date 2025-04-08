#include <iostream>
using namespace std;

class CA {
	public:
		int m_a;
		CA(int m_a_value = 0) : m_a(m_a_value) { }
		~CA() { };
};

union Test {
	CA a;
	double d;
};

int main() {
	union Test t;
	t.a = CA();
	t.d = 1.0;
	cout << t.a.m_a << endl;
	cout << t.d << endl;
	return 0;
}