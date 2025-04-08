#include<iostream>
using namespace std;

class rectangle {
private:
	double x1;
	double x2;
	double y1;
	double y2;
public:
	rectangle(double x1, double y1, double x2, double y2) :x1(x1), y1(y1), x2(x2), y2(y2) {};
	double getArea();
};

double rectangle::getArea()
{
	return abs(x1 - x2) * abs(y1 - y2);
}

int main()
{
	rectangle test(1, 1, 5, 5);
	cout << test.getArea();
	return 0;
}