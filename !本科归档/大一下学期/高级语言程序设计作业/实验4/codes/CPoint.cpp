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
	//��Ա�����������
	void coculate1();
	//��Ԫ�����������
	friend void coculate2(CPoint &);
	//�ⲿ�ӿ�
	double outx();
	double outy();
};
//һ�㺯���������
void coculate3(CPoint &);


//��������
double CPoint::outx() {
	return this->x;
}
double CPoint::outy() {
	return this->y;
}

void CPoint::coculate1() {
	cout << "��Ա��������Ϊ:" << endl;
	cout << sqrt(x * x + y * y) << endl;
}
void coculate2(CPoint &t) {
	cout << "��Ԫ��������Ϊ:" << endl;
	cout << sqrt(t.x * t.x + t.y * t.y) << endl;
}
void coculate3(CPoint& t) {
	cout << "һ�㺯������Ϊ:" << endl;
	cout << sqrt(t.outx() * t.outx() + t.outy() * t.outy()) << endl;
}


int main() {
	CPoint a(1.0, 1.0);
	a.coculate1();
	coculate2(a);
	coculate3(a);
	return 0;
}