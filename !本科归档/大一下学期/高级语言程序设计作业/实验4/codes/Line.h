#pragma once
#ifndef LINE_H
#define LINE_H
#include"Point.h"
//������
class Line {	//Line��Ķ���
public:	//�ⲿ�ӿ�
    Line(Point xp1, Point xp2);
    Line(Line& l);
    ~Line() { count--; }
    static int counts();
    double getLen() { return len; }
private:	//˽�����ݳ�Ա
    static int count;
    Point p1, p2;	//Point��Ķ���p1,p2
    double len;
};

#endif // !LINE_H

