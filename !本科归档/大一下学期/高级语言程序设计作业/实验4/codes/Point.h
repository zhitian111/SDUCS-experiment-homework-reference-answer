#pragma once
#ifndef POINT_H
#define POINT_H
class Point {	//Point¿‡∂®“Â
public:
    Point(int xx = 0, int yy = 0) {
        x = xx;
        y = yy;
    }

    Point(Point& p);
    int getX() { return x; }
    int getY() { return y; }
private:
    int x, y;

};

#endif
