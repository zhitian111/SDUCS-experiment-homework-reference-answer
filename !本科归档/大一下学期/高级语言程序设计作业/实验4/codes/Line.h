#pragma once
#ifndef LINE_H
#define LINE_H
#include"Point.h"
//类的组合
class Line {	//Line类的定义
public:	//外部接口
    Line(Point xp1, Point xp2);
    Line(Line& l);
    ~Line() { count--; }
    static int counts();
    double getLen() { return len; }
private:	//私有数据成员
    static int count;
    Point p1, p2;	//Point类的对象p1,p2
    double len;
};

#endif // !LINE_H

