#pragma once
#include <vector>
#include <set>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string>

struct Point
{
    int value = 0;
    char sign = '*';
    bool bomb = false;
};

class Saper
{
private:
    Point point;
    std::vector<Point> board;
    std::set<int> bomb;
    HANDLE hOut;
    int position;
    int sound;
    unsigned int points;
    int flagsCounter;
    void createField();
    void showField(const int&);
    void randomBomb();
    void setBomb();
    void setPointsAroundBombs();
    void showInformation();
    void setColor(const std::string&);
    void playSound();
    void endGame();
    void gameOptions(const std::string&);
    void resetGame();
    void win();
    bool checkFlagsLimit();
    void flag();
    void checkPosition();
    void automaticSetting(const int&, const int&);
    bool checkRightSide(const int&);
    bool checkLeftSide(const int&);
    bool checkTopSide(const int&);
    bool checkTopLeftSide(const int&);
    bool checkTopRightSide(const int&);
    bool checkDownSide(const int&);
    bool checkDownLeftSide(const int&);
    bool checkDownRightSide(const int&);
    void help();
public:
    Saper(const int& sound_, const int& points_);
    ~Saper();
    void checkButton();
};

