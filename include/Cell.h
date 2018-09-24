#ifndef CELL_H
#define CELL_H
#include "Point.h"

class Cell
{
private:
    int value;
    bool isWritten;
    Point coord;
    bool flag;

public:
    Cell(const int _value, const bool _isWritten, const Point _point, const bool _flag);

    Cell(const int _value, const bool _isWritten);

    Cell();

    void setCell(const int _value, const bool _isWritten, const Point _point, const bool _flag);

    void setValue(const int _value);

    void setWrite(const bool _isWritten);

    void setFlag(const bool _flag);

    void setCoord(const int x, const int y);

    int getValue();

    bool wrote();

    bool isFlag();



    Point getPosition();

    void printPosition();
};

#endif // CELL_H
