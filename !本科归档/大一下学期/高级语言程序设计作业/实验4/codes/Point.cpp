#include"Line.h"
#include"Point.h"
#include<iostream>
using namespace std;
Point::Point(Point& p) {	//���ƹ��캯����ʵ��
    x = p.x;
    y = p.y;
    cout << "Calling the copy constructor of Point" << endl;
}
