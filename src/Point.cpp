#include "Point.h"

    Point::Point(const int _x, const int _y){
        x = _x;
        y = _y;
    }

    Point::Point(){
        Point(0, 0);
    }

    void Point::setPoint(int _x, int _y){
        x = _x;
        y = _y;
    }

    Point Point::getPoint(){
        return Point(x, y);
    }

    int Point::getX(){
        return x;
    }

    int Point::getY(){
        return y;
    }
