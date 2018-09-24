#include <stdio.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <list>
#include <queue>
#include <conio.h>
#include <string>
#include <cstdlib>

//thư viện đồ họa
#include <graphics.h>

//thư viện của mình
#include "Point.h"
#include "Cell.h"
#include "Field.h"


//dữ liệu về chế độ easy
#define EASY_SIZE_HEIGHT 9
#define EASY_SIZE_WIDTH 9
#define EASY_MINES 10

//dữ liệu về chế độ medium
#define MEDIUM_SIZE_HEIGHT 16
#define MEDIUM_SIZE_WIDTH 16
#define MEDIUM_MINES 40

//dư liệu về chế độ hard
#define HARD_SIZE_HEIGHT 16
#define HARD_SIZE_WIDTH 30
#define HARD_MINES 99

// kích thước màn hình
#define WINDOW_WIDTH 1100
#define WINDOW_HEIGHT 700

// thông số cho mỗi cell kích thước 30 và cách nhau 5
#define CELL_SIZE 30
#define SPACE_SIZE 4

using namespace std;

Point getCoordLMouseRelease(){
    int x, y;
    while(GetAsyncKeyState(VK_LBUTTON)){
        x = mousex();
        y = mousey();
    }
    Point point(x,y);
    return point;
}

Point getCoordRMouseRelease(){
    int x, y;
    while(GetAsyncKeyState(VK_RBUTTON)){
        x = mousex();
        y = mousey();
    }
    Point point(x,y);
    return point;
}

// tạo màn hình giới thiệu về game
void introScene(){

    // màn hình giới thiệu game
    settextstyle(4, HORIZ_DIR, 7);
    int introHeight = textheight("MINESWEEPER");
    int introWidth = textwidth("MINESWEEPER");
    outtextxy(WINDOW_WIDTH/2 - introWidth/2, WINDOW_HEIGHT/2 - introHeight/2 - 100, "MINESWEEPER");

    // đợi để load đến màn hình chọn mode
    delay(2000);
    graphdefaults();
    cleardevice();
}

// chọn chế độ chơi
void choseModeGameScene(Field *field){
    cout << "che do choi: 1=easy, 2=medium, 3=hard " << endl;
    int mode;

    delay(500);

    // tạo chữ "Mode game"
    settextstyle(4, HORIZ_DIR, 6);
    int introHeight = textheight("Mode game");
    int introWidth = textwidth("Mode game");
    outtextxy(WINDOW_WIDTH/2 - introWidth/2, 50, "Mode game");

    delay(500);

    //tạo các ô để chọn chế độ chơi
    setcolor(0);


    for(int i = 1; i <= 3; ++i){

        /** modeName lưu trữ tên mode:
        1 sẽ là EASY
        2 sẽ là MEDIUM
        3 sẽ là HARD **/

        char modeName[6];
        if(i == 1){
            sprintf(modeName, "EASY");
        } else if (i == 2){
            sprintf(modeName, "MEDIUM");
        } else {
            sprintf(modeName, "HARD");
        }

        /** Tạo ô **/
        bar(WINDOW_WIDTH/2 - 100, 75 + 80*i, WINDOW_WIDTH/2 + 100, 75 + 80*i + 60);

        /** thiết lập kiểu text **/
        setbkcolor(15);
        setcolor(0);
        settextstyle(4, HORIZ_DIR, 3);

        /** show text **/
        int modeNameHeight = textheight(modeName);
        int modeNameWidth = textwidth(modeName);
        outtextxy(WINDOW_WIDTH/2 - modeNameWidth/2, 75 + 80*i + 30 - modeNameHeight/2, modeName);

        /** set thời gian cho xuất hiện ô tiếp theo **/
        delay(100);
    }

    /** Chọn chế độ chơi **/
    do{
        delay(1);
        /** GetAsyncKeyState(VK_LBUTTON): xem click chuột trái diễn ra hay không **/
        if(GetAsyncKeyState(VK_LBUTTON)){

            /** mousex() và mousey() là tọa độ của con chuột tại thời điểm click **/
            Point LMouseRelease = getCoordLMouseRelease();
            int x = LMouseRelease.getX();
            int y = (LMouseRelease.getY() - 75)/80;

            /** kiểm tra xem đã click chọn vào ô mode chưa **/
            if (x >= WINDOW_WIDTH/2 - 100 && x <= WINDOW_WIDTH/2 + 100 && y >= 1 && y <= 3){

                mode = y;
                /** khi đã chọn đúng ô thì tô viền đỏ cho ô đó đánh dấu đã chọn **/
                for(int i = 0; i <= 5; ++i){
                    setcolor(RED);
                    rectangle(WINDOW_WIDTH/2 - 100 + i, 75 + 80*y + i,
                              WINDOW_WIDTH/2 + 100 - i, 75 + 80*y + 60 - i);
                }

                delay(500);

                /** đã chọn chế độ thì break khỏi vòng lặp **/
                break;
            }
        }
    } while(1);

    /** thiết lập bãi mìn tương ứng với chế độ chơi **/
    if (mode == 1){
        field->createField(EASY_SIZE_HEIGHT, EASY_SIZE_WIDTH, EASY_MINES);
    } else if (mode == 2){
        field->createField(MEDIUM_SIZE_HEIGHT, MEDIUM_SIZE_WIDTH, MEDIUM_MINES);
    } else if (mode == 3){
        field->createField(HARD_SIZE_HEIGHT, HARD_SIZE_WIDTH, HARD_MINES);
    }

    cout << "Ban chon mode " << mode << endl;

    /** đưa về trạng thái graph default **/
    delay(10);
    graphdefaults();
    cleardevice();
}


void gameScene(Field* field){
    int height = field->getHeight();
    int width = field->getWidth();
    int mineNumbet = field->getMineNumber();

    int LEFT_COORD_FIELD = (WINDOW_WIDTH - width*(CELL_SIZE + SPACE_SIZE))/2;
    int TOP_COORD_FIELD = 115;

    /** hiện tính điểm lên màn hình game **/
    char scoreString[20];
    sprintf(scoreString,"Score: %d", field->getScore());
    settextstyle(4, HORIZ_DIR, 3);
    outtextxy(100, TOP_COORD_FIELD - textheight(scoreString) - 50, scoreString);

    /** Hiện số Flag lên màn hình game **/
    char flagChar[20];
    sprintf(flagChar, "Flag: %d", field->getNumberFlag());
    settextstyle(4, HORIZ_DIR, 3);
    outtextxy(750, TOP_COORD_FIELD - textheight(flagChar) - 50, flagChar);

    /** tạo nút ấn quay lại phần chọn mode **/
    bar(WINDOW_WIDTH/2 - 150, 30 ,WINDOW_WIDTH/2 + 150, 85);
    setbkcolor(15);
    setcolor(0);
    outtextxy(WINDOW_WIDTH/2 - textwidth("CHANGE MODE")/2, 55 - textheight("CHANGE MODE")/2,"CHANGE MODE");

    /** tạo field cho ra màn hình **/
    setfillstyle(SOLID_FILL, 9);
    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            int left   = i*(CELL_SIZE + SPACE_SIZE) + LEFT_COORD_FIELD;
            int top    = j*(CELL_SIZE + SPACE_SIZE) + TOP_COORD_FIELD;
            int right  = i*(CELL_SIZE + SPACE_SIZE) + LEFT_COORD_FIELD + CELL_SIZE;
            int bottom = j*(CELL_SIZE + SPACE_SIZE) + TOP_COORD_FIELD + CELL_SIZE;
            bar(left, top, right, bottom);
        }
        delay(25);
    }
    graphdefaults();

    /** kết quả của left mouse click **/
    int x;
    int y;
    bool endGame = false;
    /** vòng lặp vô hạn đợi mouse click **/
    do{
        delay(1); // dừng để có thể bắt lấy mouseclick hiệu quả hơn

        /** chuột phải để dựng flag với chức năng:
        * Khi đã dựng flag người chơi dự đoán đó là mìn và không thể click trái vào bãi mìn nữa
        * số flag tối đa mà người chơi có bằng số mìn
        * Người chơi có thể lấy lại flag bằng cách click chuột phải lần nữa
        **/
        if(GetAsyncKeyState(VK_RBUTTON) && !endGame){
            Point LMouseRelease = getCoordRMouseRelease();
            x = (LMouseRelease.getX() - LEFT_COORD_FIELD)/(CELL_SIZE + SPACE_SIZE);
            y = (LMouseRelease.getY() - TOP_COORD_FIELD)/(CELL_SIZE + SPACE_SIZE);

            if(x >= 0 && x < width && y >= 0 && y < height){
                if(field->getCell(x, y)->isFlag()){
                    field->deleteFlag(x, y);

                    setfillstyle(SOLID_FILL, 9);
                    int left   = x*(CELL_SIZE + SPACE_SIZE) + LEFT_COORD_FIELD;
                    int top    = y*(CELL_SIZE + SPACE_SIZE) + TOP_COORD_FIELD;
                    int right  = x*(CELL_SIZE + SPACE_SIZE) + LEFT_COORD_FIELD + CELL_SIZE;
                    int bottom = y*(CELL_SIZE + SPACE_SIZE) + TOP_COORD_FIELD + CELL_SIZE;
                    bar(left, top, right, bottom);
                    delay(0);
                } else if (!field->getCell(x, y)->wrote() && field->getNumberFlag() > 0) {
                    field->choseToFlag(x, y);

                    setfillstyle(SOLID_FILL, RED);
                    setcolor(RED);
                    int flag[8] = {3, 3, 27, 12, 3, 21, 3, 3};
                    for(int i = 0; i < 8; ++i){
                        if(i%2 == 0) flag[i] += x*(CELL_SIZE + SPACE_SIZE) + LEFT_COORD_FIELD;
                        else flag[i] += y*(CELL_SIZE + SPACE_SIZE) + TOP_COORD_FIELD;
                    }
                    fillpoly(4, flag);

                    for(int i = 0; i < 3; ++i){
                        int startx = 3 + i + x*(CELL_SIZE + SPACE_SIZE) + LEFT_COORD_FIELD;
                        int starty = 12 + y*(CELL_SIZE + SPACE_SIZE) + TOP_COORD_FIELD;
                        int endx = 3 + i + x*(CELL_SIZE + SPACE_SIZE) + LEFT_COORD_FIELD;
                        int endy = 27 + y*(CELL_SIZE + SPACE_SIZE) + TOP_COORD_FIELD;
                        line(startx, starty, endx, endy);
                    }
                    delay(1);
                }

            }
            setbkcolor(0);
            setcolor(15);
            sprintf(flagChar, "Flag: %d  ", field->getNumberFlag());
            settextstyle(4, HORIZ_DIR, 3);
            outtextxy(750, TOP_COORD_FIELD - textheight(flagChar) - 50, flagChar);
        }

        /** chuột trái để chọn mở các ô **/
        if(GetAsyncKeyState(VK_LBUTTON)){
            /** x, y trả về vị trí hiện tại của chuột **/
            Point LMouseRelease = getCoordLMouseRelease();
            x = LMouseRelease.getX();
            y = LMouseRelease.getY();

            /** chọn vào change mode thì quay lại màn hình chọn mode **/
            if(x >= WINDOW_WIDTH/2 - 150 && x <= WINDOW_WIDTH/2 + 150 && y >= 30 && y <= 85){
                setcolor(RED);
                for(int i = 0; i <= 5; ++i){
                    rectangle(WINDOW_WIDTH/2 - 150 + i, 30 + i, WINDOW_WIDTH/2 + 150 - i, 85 - i);
                }
                delay(500);
                break;
            }
            /** chọn ngoài mode change **/
            else if(!endGame){
                /** tính lại x, y để đưa ra chỉ số của ô đang chọn **/
                x = (x - LEFT_COORD_FIELD)/(CELL_SIZE + SPACE_SIZE);
                y = (y - TOP_COORD_FIELD)/(CELL_SIZE + SPACE_SIZE);

                /** chọn một ô trong filed **/
                if (x >= 0 && x < width && y >= 0 && y < height){
                    int result = field->choseCell(x, y);         /** BFS ô vừa chọn **/

                    /** in ra kết quả **/
                    for (int i = 0; i < width; ++i){
                        for(int j = 0; j < height; ++j){
                            if(field->getCell(i, j)->wrote()){

                                setfillstyle(SOLID_FILL, 15); /** set màu ô trắng **/
                                setbkcolor(15);

                                /** tính giá trị tại ô đó để căn cứ vào đó hiện giá trị và màu tương ứng **/
                                int value = field->getCell(i, j)->getValue();
                                setcolor(value + 1);

                                /** khi chọn đúng ô mìn sẽ bôi đỏ ô đó **/
                                if(value == 9 && x == i && y == j){
                                    setfillstyle(SOLID_FILL, RED);
                                }

                                /** tạo một ô màu tương ứng **/
                                int left   = i*(CELL_SIZE + SPACE_SIZE) + LEFT_COORD_FIELD;
                                int top    = j*(CELL_SIZE + SPACE_SIZE) + TOP_COORD_FIELD;
                                int right  = i*(CELL_SIZE + SPACE_SIZE) + LEFT_COORD_FIELD + CELL_SIZE;
                                int bottom = j*(CELL_SIZE + SPACE_SIZE) + TOP_COORD_FIELD + CELL_SIZE;
                                bar(left, top, right, bottom);

                                /** Hiện giá trị của ô đó
                                *   Nếu bằng 0 thì không hiện giá trị
                                *   Nếu bằng 1->8 thì hiện giá trị
                                *   Nếu bằng 9 hiện một chấm tròn to màu đen(tượng trưng là mìn)
                                **/
                                if(value != 0 && value != 9){
                                    settextstyle(4, HORIZ_DIR, 2);
                                    char valueChar[1];
                                    sprintf(valueChar,"%d", value);
                                    outtextxy(left + (CELL_SIZE - textwidth(valueChar))/2,
                                            top + (CELL_SIZE - textheight(valueChar))/2, valueChar);
                                }
                                else if (value == 9){
                                    for (int radius = 0; radius <= CELL_SIZE/2 - 3; ++radius){
                                        setcolor(0);
                                        circle((left + right)/2, (top + bottom)/2 , radius);
                                    }
                                }
                            }
                        }
                    }

                    if (result == 1){
                        /** Hiện "WIN"**/
                        setbkcolor(0);
                        setcolor(15);
                        settextstyle(4, HORIZ_DIR, 4);
                        outtextxy(950, TOP_COORD_FIELD - textheight("WIN") - 50,"WIN");
                        endGame = true;

                    } else if (result == 2){
                        /** hiện "DIE" **/
                        setbkcolor(0);
                        setcolor(15);
                        settextstyle(4, HORIZ_DIR, 4);
                        outtextxy(950, TOP_COORD_FIELD - textheight("DIE") - 50,"DIE");
                        endGame = true;
                    }

                }
            }
        }
        /** Cập nhật lại điểm sau mỗi lần mở được ô **/
        setbkcolor(0);
        setcolor(15);
        sprintf(scoreString,"Score: %d", field->getScore());
        settextstyle(4, HORIZ_DIR, 3);
        outtextxy(100, TOP_COORD_FIELD - textheight(scoreString) - 50,scoreString);
    } while(1);


    cleardevice();
    graphdefaults();
}

int main(){
    srand(time(0));

    Field fieldGame; //tạo một bảng game
    int height, width, mineNumber;

    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT);

    // màn hình giới thiệu
    introScene();

    do{
        // lựa chọn chế độ chơi bằng cách click vào màn hình.
        choseModeGameScene(&fieldGame);

        // màn hình chính
        gameScene(&fieldGame);
    } while(1);

    getch();
    closegraph();
}
