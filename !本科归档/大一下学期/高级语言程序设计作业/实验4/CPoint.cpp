#include<iostream>
#include<cmath>
using namespace std;


class CPoint
{
private:
	double x;
	double y;
public:
	CPoint(double xx = 0,double yy=0):x(xx),y(yy){}
	//成员函数计算距离
	void coculate1();
	//友元函数计算距离
	friend void coculate2(CPoint &);
	//外部接口
	double outx();
	double outy();
};
//一般函数计算距离
void coculate3(CPoint &);


//函数定义
double CPoint::outx() {
	return this->x;
}
double CPoint::outy() {
	return this->y;
}

void CPoint::coculate1() {
	cout << "成员函数计算为:" << endl;
	cout << sqrt(x * x + y * y) << endl;
}
void coculate2(CPoint &t) {
	cout << "友元函数计算为:" << endl;
	cout << sqrt(t.x * t.x + t.y * t.y) << endl;
}
void coculate3(CPoint& t) {
	cout << "一般函数计算为:" << endl;
	cout << sqrt(t.outx() * t.outx() + t.outy() * t.outy()) << endl;
}


int main() {
	CPoint a(1.0, 1.0);
	a.coculate1();
	coculate2(a);
	coculate3(a);
	return 0;
}