#include "Cell.h"
#include "Point.h"
#include <iostream>

using namespace std;

    Cell::Cell(const int _value, const bool _isWritten, const Point _point, const bool _flag){
        value = _value;
        isWritten = _isWritten;
        coord = _point;
    }

    Cell::Cell(const int _value, const bool _isWritten){
        Point point;
        Cell(_value, _isWritten, point, false);
    }

    Cell::Cell(){
        Point point;
        Cell(0, false, point, false);
    }

    void Cell::setCell(const int _value, const bool _isWritten, const Point _point, const bool _flag){
        value = _value;
        isWritten = _isWritten;
        coord = _point;
        flag = _flag;
    }

    void Cell::setValue(const int _value){
        value = _value;
    }

    void Cell::setFlag(const bool _flag){
        flag = _flag;
    }

    int Cell::getValue(){
        return value;
    }

    void Cell::setWrite(const bool _isWritten){
        isWritten = _isWritten;
    }

    bool Cell::wrote(){
        return isWritten;
    }

    void Cell::setCoord(const int x, const int y){
        coord.setPoint(x, y);
    }

    Point Cell::getPosition(){
        return coord;
    }

    bool Cell::isFlag(){
        return flag;
    }

    void Cell::printPosition(){
        cout << coord.getX() << " " << coord.getY() << endl;
    }
