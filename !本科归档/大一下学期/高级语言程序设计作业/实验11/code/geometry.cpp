#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#define PI 3.1415926
using namespace std;

class R {
public:
	int a;
	int b;
	int s;
	void coculate()
	{
		s = a * b;
	}
	R(int a, int b) :a(a), b(b) { coculate(); };
};
class C {
public:
	int r;
	double s;
	void coculate()
	{
		s = r * r * PI;
	}
	C(int r) :r(r) { coculate(); };

};
class T {
public:
	int a;
	int b;
	int c;
	double s;
	void coculate()
	{
		double p = (a + b + c) / 2.0;
		s = sqrt(p * (p - a) * (p - b) * (p - c));
	}
	T(int a, int b, int c) :a(a), b(b), c(c) { coculate(); };

};

bool Tcompare(T A, T B)
{
	return A.s < B.s;
}

bool Rcompare(R A, R B)
{
	return A.s < B.s;
}

bool Ccompare(C A, C B)
{
	return A.s < B.s;
}
vector<R> r;
vector<C> c;
vector<T> t;
int main()
{
	int n;
	cin >> n;
	char mark = '\0';
	for (int i = 0; i < n; i++)
	{
		cin >> mark;
		switch (mark)
		{
		case 'R':
			int a, b;
			cin >> a >> b;
			R* tem = new R(a, b);
			r.push_back(*tem);
			break;
		case 'C':
			int a;
			cin >> a;
			C* temp = new C(a);
			c.push_back(*temp);
			break;
		case 'T':
			int a, b, c;
			cin >> a >> b >> c;
			T* te = new T(a, b, c);
			t.push_back(*te);
		default:
			break;
		}
	}
	sort(r.begin(), r.end(), Rcompare);
	sort(t.begin(), t.end(), Tcompare);
	sort(c.begin(), c.end(), Ccompare);

}