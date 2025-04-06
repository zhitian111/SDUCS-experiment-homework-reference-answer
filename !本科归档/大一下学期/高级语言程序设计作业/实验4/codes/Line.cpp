#include"Line.h"
#include"Point.h"
#include<iostream>
using namespace std;
//�����Ĺ��캯��

int Line::count = 0;

Line::Line(Point xp1, Point xp2) : p1(xp1), p2(xp2) {
    cout << "Calling constructor of Line" << endl;
    double x = static_cast<double>(p1.getX() - p2.getX());
    double y = static_cast<double>(p1.getY() - p2.getY());
    len = sqrt(x * x + y * y);
    count++;
}

//�����ĸ��ƹ��캯��
Line::Line(Line& l) : p1(l.p1), p2(l.p2) {
    cout << "Calling the copy constructor of Line" << endl;
    len = l.len;
    count++;
}

int Line::counts() {
    return count;
}