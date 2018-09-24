#ifndef FIELD_H
#define FIELD_H

#include "Field.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <list>
#include <queue>
#include "Point.h"
#include "Cell.h"

class Field{
private:
    Cell cells[30][16];
    int height, width, minesNumber;
    int score;
    int maxScore;
    bool endGame;
    int numberFlag;

public:
    Field(const int _height, const int _width, const int _minesNumber);

    Field();

    void setHeight(const int _height);

    void setWidth(const int _width);

    void setMineNumber(const int _minesNumber);

    int getHeight();

    int getWidth();

    int getMineNumber();


    int getScore();

    bool isEnd();

    Cell* getCell(Point point);

    Cell* getCell(int x, int y);

    void createField(const int _height, const int _width, const int _minesNumber);

    void createField();

    // Đưa ra tập hợp các ô xung quang một ô
    std::list<Cell*> getNeighbors(Cell* cell);

    // Loang ra khi chọn được một ô có value = 0.
    void BFSValue(Cell* cell);

    // chọn cell và đưa ra kết quả
    int choseCell(Cell* cell);

    int choseCell(Point point);

    int choseCell(int x, int y);

    void choseToFlag(int x, int y);

    void deleteFlag(int x, int y);

    int getNumberFlag();

    void printOut();
};


#endif // FIELD_H
