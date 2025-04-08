#include"Line.h"
#include"Point.h"
#include<iostream>
using namespace std;
Point::Point(Point& p) {	//复制构造函数的实现
    x = p.x;
    y = p.y;
    cout << "Calling the copy constructor of Point" << endl;
}
