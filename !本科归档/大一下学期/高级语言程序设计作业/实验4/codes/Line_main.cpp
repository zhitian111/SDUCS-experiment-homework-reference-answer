#include"Line.h"
#include"Point.h"
#include<iostream>
using namespace std;
//������
int main() {
    Point myp1(1, 1), myp2(4, 5);	//����Point��Ķ���
    Line line(myp1, myp2);	//����Line��Ķ���
    Line line2(line);	//���ø��ƹ��캯������һ���¶���
    cout << "The length of the line is: ";
    cout << line.getLen() << endl;
    cout << "The length of the line2 is: ";
    cout << line2.getLen() << endl;
    cout << "The number of Lines is " << Line::counts() << endl;
    return 0;
}