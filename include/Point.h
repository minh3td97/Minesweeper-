#ifndef POINT_H
#define POINT_H


class Point
{
private:
    int x;
    int y;

public:
    Point(const int _x, const int _y);

    Point();

    void setPoint(int _x, int _y);

    Point getPoint();

    int getX();

    int getY();
};

#endif // POINT_H
