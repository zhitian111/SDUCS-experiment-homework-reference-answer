#include<iostream>
#include<cmath>
using namespace std;
class Point
{
private:
	double _x;
	double _y;
public:
	Point operator ++();
	Point operator ++(int);
	Point operator --();
	Point operator --(int);
	Point(double x,double y):_x(x),_y(y){}
	void show();
};
void Point::show()
{
	cout << "_x=" << _x << endl << "_y=" << _y << endl;
}
Point Point::operator++(int)
{
	Point temp = *this;
	this->_x += sqrt(2) / 2;
	this->_y += sqrt(2) / 2;
	return temp;
}
Point Point::operator++()
{
	this->_x += sqrt(2) / 2;
	this->_y += sqrt(2) / 2;
	return *this;
}
Point Point::operator--(int)
{
	Point temp = *this;
	this->_x -= sqrt(2) / 2;
	this->_y -= sqrt(2) / 2;
	return temp;
}
Point Point::operator--()
{
	this->_x -= sqrt(2) / 2;
	this->_y -= sqrt(2) / 2;
	return *this;
}
int main()
{
	Point p(1.0, 1.0);
	p.show();
	p++.show();
	(++p).show();
	(--p).show();
	p--.show();
	return 0;
}