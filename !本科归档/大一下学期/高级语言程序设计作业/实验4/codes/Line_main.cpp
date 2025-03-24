#include"Line.h"
#include"Point.h"
#include<iostream>
using namespace std;
//主函数
int main() {
    Point myp1(1, 1), myp2(4, 5);	//建立Point类的对象
    Line line(myp1, myp2);	//建立Line类的对象
    Line line2(line);	//利用复制构造函数建立一个新对象
    cout << "The length of the line is: ";
    cout << line.getLen() << endl;
    cout << "The length of the line2 is: ";
    cout << line2.getLen() << endl;
    cout << "The number of Lines is " << Line::counts() << endl;
    return 0;
}