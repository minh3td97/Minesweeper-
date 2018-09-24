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

using namespace std;


    Field::Field(const int _height, const int _width, const int _minesNumber){
        createField(_height, _width, _minesNumber);
    }

    Field::Field(){
        score = 0;
    }

    void Field::setHeight(const int _height){
        height = _height;
    }

    int Field::getHeight(){
        return height;
    }

    int Field::getWidth(){
        return width;
    }

    int Field::getMineNumber(){
        return minesNumber;
    }

    void Field::setWidth(const int _width){
        width = _width;
    }

    void Field::setMineNumber(const int _minesNumber){
        minesNumber = _minesNumber;
    }

    int Field::getScore(){
        return score;
    }

    bool Field::isEnd(){
        return endGame;
    }

    Cell* Field::getCell(Point point){
        return &cells[point.getX()][point.getY()];
    }

    Cell* Field::getCell(int x, int y){
        Point point(x, y);
        return getCell(point);
    }

    void Field::createField(const int _height, const int _width, const int _minesNumber){
        height = _height;
        width = _width;
        minesNumber = _minesNumber;
        score = 0;
        maxScore = height*width - minesNumber;
        endGame = false;
        numberFlag = minesNumber;

        // tạo mảng 2 chiều có chiều height và độ rộng width bằng 0
        for(int i = 0; i < width; ++i){
            for(int j = 0; j < height; ++j){
                Point point(i, j);
                cells[i][j].setCell(0, false, point, false);
            }
        }

        // Tạo random bãi mìn
        for(int mines = 0; mines < minesNumber; ++mines){
            int i, j;
            do{
                i = rand()% width;
                j = rand()% height;

            } while (cells[i][j].getValue() == 9);
            cells[i][j].setValue(9);

        }

        // tính value tại mỗi ô.
        for (int i = 0; i < width; ++i){
            for(int j = 0; j < height; ++j){
                if (cells[i][j].getValue() != 9){
                    int counting = 0;

                    list<Cell*> neighbor = getNeighbors(&cells[i][j]);

                    list<Cell*>::iterator tempNeighbor = neighbor.begin();

                    for(tempNeighbor; tempNeighbor != neighbor.end(); ++tempNeighbor){
                        if ((*tempNeighbor)->getValue() == 9) ++counting;
                    }

                    cells[i][j].setValue(counting);
                }
            }
        }
    }

    void Field::createField(){
        createField(height, width, minesNumber);
    }

    // Đưa ra tập hợp các ô xung quang một ô
    std::list<Cell*> Field::getNeighbors(Cell* cell){

        int x = cell->getPosition().getX();
        int y = cell->getPosition().getY();

        list<Cell*> neighbors;

        for (int i = -1; i <= 1; ++i){
            for(int j = -1; j <= 1; ++j){
                if (i != 0 || j != 0){
                    if(x + i >= 0 && x + i < width && y + j >= 0 && y + j < height){
                        Point point(x + i, y + j);
                        neighbors.push_back(getCell(point));
                    }
                }
            }
        }
        return neighbors;
    }

    // Loang ra khi chọn được một ô có value = 0.
    void Field::BFSValue(Cell* cell){
        queue<Cell*> zeroDomain;

        cell->setWrite(true);
        ++score;

        zeroDomain.push(cell);

        while (!zeroDomain.empty()){
            Cell* tempCell = zeroDomain.front();

            zeroDomain.pop();

            list<Cell*> neighbor = getNeighbors(tempCell);

            list<Cell*>::iterator tempNeighbor = neighbor.begin();

            for(tempNeighbor; tempNeighbor != neighbor.end(); ++tempNeighbor){
                if(!(*tempNeighbor)->isFlag()){
                    if ((*tempNeighbor)->getValue() == 0 && !(*tempNeighbor)->wrote()){
                        (*tempNeighbor)->setWrite(true);
                        ++score;
                        zeroDomain.push(*tempNeighbor);

                    } else if ((*tempNeighbor)->getValue() != 9 && !(*tempNeighbor)->wrote()) {
                        (*tempNeighbor)->setWrite(true);
                        ++score;
                    }
                }
            }
        }
    }
    // chọn cell và đưa ra kết quả
    int Field::choseCell(Cell* cell){
        if(!cell->isFlag()){
            cout << "Chose Cell: " << cell->getPosition().getX() << " " << cell->getPosition().getY() << endl;
            if(cell->getValue() == 9 && !cell->wrote()){
                cout << "DIE" << endl;
                endGame = true;

                for(int i = 0; i < width; ++i){
                    for (int j = 0; j < height; ++j){
                        if(cells[i][j].getValue() == 9) cells[i][j].setWrite(true);
                    }
                }
                printOut();
                cout << "Your score: " << score << endl;
                return 2;
            }
            else if (cell->getValue() != 0 && !cell->wrote()){
                cell->setWrite(true);
                ++score;
                printOut();
            }
            else if(cell->getValue() == 0 && !cell->wrote()){
                BFSValue(cell);
                printOut();
            }

            if(score == maxScore){
                endGame = true;
                cout << "You win. Your score: " << maxScore << endl;
                printOut();
                return 1;
            }
            return 0;
        }
        return 0;
    }

    int Field::choseCell(Point point){
        return choseCell(getCell(point));
    }

    int Field::choseCell(int x, int y){
        Point point(x, y);
        return choseCell(point);
    }

    void Field::choseToFlag(int x, int y){
        if (!cells[x][y].wrote() && numberFlag > 0){
            cells[x][y].setFlag(true);
            --numberFlag;
            cout << "Create flag: " << x << " " << y << endl;
        }
    }

    void Field::deleteFlag(int x, int y){
        if(cells[x][y].isFlag() && numberFlag < minesNumber) {
            cells[x][y].setFlag(false);
            ++numberFlag;
            cout << "Delete flag: " << x << " " << y << endl;
        }
    }

    int Field::getNumberFlag(){
        return numberFlag;
    }

    void Field::printOut(){
        if(endGame){

            for (int j = 0; j < height; ++j){
                for (int i = 0; i < width; ++i){
                    if(cells[i][j].getValue() == 9) cout << "* ";
                    else if (cells[i][j].getValue() == 0) cout << "  ";
                    else if (!cells[i][j].wrote()) cout << "_ ";
                    else cout << cells[i][j].getValue() << " ";
                }
                cout << endl;
            }
        }
        else{
            for (int j = 0; j < height; ++j){
                for (int i = 0; i < width; ++i){
                    if(cells[i][j].wrote() && cells[i][j].getValue() != 0)
                        cout << cells[i][j].getValue() << " ";
                    else if (cells[i][j].wrote() && cells[i][j].getValue() == 0) cout << "  ";
                    else cout << "_ ";
                }
                cout << endl;
            }
        }
    }

