#include "Game.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::set;

Saper::Saper(const int& sound_, const int& position_)
    :sound(sound_)
    , points(0)
    , position(position_)
    , flagsCounter(0)
{
    createField();
    setBomb();
    setPointsAroundBombs();
    showField(0);
    showInformation();
}

Saper::~Saper() {}

void Saper::createField()
{
    for (unsigned int i = 0; i < 100; i++)
    {
        board.emplace_back(point);
    }
}

void Saper::showField(const int& loadedPosition) 
{
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    for (unsigned int i = 0; i < board.size(); i++)
    {
        if (i == loadedPosition)
            setColor("backgroundGreen");
        else
            setColor("foregroundBlue");
        if (i % 10 == 0)
            cout << endl << endl;
        if (board[i].sign == 'f')
            setColor("foregroundGreen");
        if (board[i].sign == '?')
        {
            setColor("foregroundYellow");
            cout << board[i].value << "   ";
        }
        else
            cout << board[i].sign << "   ";
    }
}

void Saper::randomBomb()
{
    int temporaryPoint;
    srand(time(nullptr));
    while (bomb.size() != 8)
    {
        temporaryPoint = rand() % 100;
        bomb.insert(temporaryPoint);
    }
}

void Saper::setBomb()
{
    randomBomb();
    for (int i = 0; i < board.size(); i++)
    {
        for (auto b : bomb)
        {
            if (i == b)
            {
                board[i].bomb = true;
                board[i].sign = '*';
                board[i].value = 9;
            }
        }
    }
}

void Saper::setPointsAroundBombs()
{
    for (auto x : bomb)
    {
        if (checkRightSide(x))                
            board[x + 1].value++;
        if (checkLeftSide(x))                    
            board[x + -1].value++;
        if (checkTopSide(x))                  
            board[x - 10].value++;
        if (checkTopLeftSide(x))               
            board[x - 11].value++;
        if (checkTopRightSide(x))
            board[x - 9].value++;
        if (checkDownSide(x))                   
            board[x + 10].value++;
        if (checkDownLeftSide(x))               
            board[x + 9].value++;
        if (checkDownRightSide(x))              
            board[x + 11].value++;
    }
}

void Saper::checkButton()
{
    if (_kbhit())
    {
        unsigned int sign;
        sign = _getch();
        switch (sign)
        {
        case 27:                                    // escape
            system("cls");
            endGame();
            break;
        case 72:                                    // UP
            system("cls");
            showField(position -= 10);
            if (position < 0)
            {
                position += 100;
                system("cls");
                showField(position);
            }
            showInformation();
            break;
        case 80:                                    // DOWN
            system("cls");
            showField(position += 10);
            if (position > 100)
            {
                position -= 100;
                system("cls");
                showField(position);
            }
            showInformation();
            break;
        case 75:                                    // <-
            system("cls");
            if (position <= 0)
                position = 100;
            showField(--position);
            showInformation();
            break;
        case 77:                                   // ->
            system("cls");
            if (position >= 99)
                position = -1;
            showField(++position);
            showInformation();
            break;
        case 13:                                  //enter
            checkPosition();
            system("cls");
            showField(position);
            showInformation();
            break;
        case 102:                                 // flag
            flag();
            system("cls");
            showField(position);
            showInformation();
            win();
            break;
        case 32:                                 // sounds
            playSound();
        }
    }
}

void Saper::showInformation()
{
    setColor("foregroundWhite");
    cout << endl << "Position: " << position + 1 << "\t|\t";
    cout << "Arrows:\tmove" << endl;
    cout << "Song: " << sound << "\t\t|\t";
    cout << "Space:\tmusic" << endl;
    cout << "Flags: " << flagsCounter << "\t|\t";
    cout << "Escape:\texit" << endl;
    //cout << "Points: " << points << endl << endl;
    //cout << "Bombs position: "; help();
}

void Saper::setColor(const std::string& color)
{
    if (color == "foregroundYellow")
        SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN);
    if (color == "foregroundBlue")
        SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
    if (color == "foregroundRed")
        SetConsoleTextAttribute(hOut, FOREGROUND_RED);
    if (color == "foregroundGreen")
        SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
    if (color == "foregroundWhite")
        SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
    if (color == "backgroundGreen")
        SetConsoleTextAttribute(hOut, BACKGROUND_GREEN);
}

void Saper::playSound()
{
    ++sound;
    switch (sound)
    {
    case 0:
        PlaySound(nullptr, 0, 0);
        break;
    case 1:
        sndPlaySound("../Sounds/Alan_Walker-Spectre.wav", SND_ASYNC);
        break;
    case 2:
        sndPlaySound("../Sounds/Ahrix-Nova.wav", SND_ASYNC);
        break;
    case 3:
        sndPlaySound("../Sounds/Different-My_heart.wav", SND_ASYNC);
        break;
    case 4:
        sndPlaySound("../Sounds/Disfigure-Blank.wav", SND_ASYNC);
        break;
    case 5:
        sndPlaySound("../Sounds/Spektrem-Shine.wav", SND_ASYNC);
        break;
    case 6:
        sndPlaySound("../Sounds/Tobu-Hope.wav", SND_ASYNC);
        break;
    case 7:
        sndPlaySound("../Sounds/Alan_Walker-Faded.wav", SND_ASYNC);
        break;
    default:
        sound = -1;
        break;
    }
    if (sound != -1)
    {
        system("cls");
        showField(position);
        showInformation();
    }
}

void Saper::endGame()
{
    unsigned int sign;
    setColor("foregroundWhite");
    cout << "Are you sure ? <y/n>" << endl;
    sign = _getch();
    if (sign == 121) // YES
        exit(0);
    if (sign == 110) // NO
    {
        system("cls");
        showField(position);
        showInformation();
    }
    else if (sign != 121 || sign != 110)
    {
        cout << "\a";
        system("cls");
        endGame();
    }
}

bool Saper::checkFlagsLimit()
{
    if (flagsCounter < 8)
        return true;
    else
        return false;
}

void Saper::flag()
{

    if (checkFlagsLimit())
    {
        if (board[position].sign == '*')
        {
            board[position].sign = 'f';
            ++flagsCounter;
            if (board[position].value == 9)
                ++points;
        }
        else if (board[position].sign == 'f')
        {
            board[position].sign = '*';
            --flagsCounter;
            if (board[position].value == 9)
                --points;
        }
    }
    else
    {
        if (board[position].sign == 'f')
        {
            board[position].sign = '*';
            --flagsCounter;
            if (board[position].value == 9)
                --points;
        }
    }
}

void Saper::gameOptions(const string& decision)
{
    unsigned int sign;
    setColor("foregroundWhite");
    system("cls");
    cout << decision << endl;
    cout << "Do you want to play once again ? <y/n>" << endl;
    sign = _getch();
    if (sign == 110) // NO
        exit(0);
    if (sign == 121) // YES
    {
        system("cls");
        resetGame();
        showField(0);
        showInformation();
    }
    else if (sign != 121 || sign != 110)
    {
        cout << "\a";
        system("cls");
        gameOptions(decision);
    }
}

void Saper::resetGame()
{
    board.clear();
    bomb.clear();
    createField();
    setBomb();
    setPointsAroundBombs();
    flagsCounter = 0;
    points = 0;
}

void Saper::win()
{
    if (points == 8)
    {
        gameOptions("Bravo, You won");
    }
}

void Saper::checkPosition()
{
    if (board[position].bomb)
        gameOptions("Unfortunately you lost");
    else
    {
        automaticSetting(position, 1);
        automaticSetting(position, 2);
    }
}

void Saper::help()
{
    for (auto x = bomb.begin(); x != bomb.end(); x++)
    {
        cout << *x + 1 << " ";
    }
}

void Saper::automaticSetting(const int& p, const int& side)
{    
    if (board[p].value == 0)
        board[p].sign = ' ';
    if (board[p].sign == 'f')
        --flagsCounter;
    
    if (board[p].value != 9 && board[p].value != 0)
    {
        if (board[p].sign == 'f')
            --flagsCounter;
        board[p].sign = '?';
        return;
    }

    switch (side)
    {
    case 1:
        if (checkRightSide(p))
            automaticSetting(p + 1, 1);
        if (checkDownSide(p))
            automaticSetting(p + 10, 1);
        if (checkDownLeftSide(p))
            automaticSetting(p + 9, 1);
        if (checkDownRightSide(p))
            automaticSetting(p + 11, 1);
        break;
    case 2:
        if (checkLeftSide(p))
            automaticSetting(p - 1, 2);
        if (checkTopSide(p))
            automaticSetting(p - 10, 2);
        if (checkTopRightSide(p))
            automaticSetting(p - 9, 2);
        if(checkTopLeftSide(p))
        automaticSetting(p - 11, 2);
        break;
    }
} 

bool Saper::checkRightSide(const int& x)
{
    if (x + 1 < 100 && board[x + 1].value != 9 && ((x + 1) % 10 != 0))
        return true;
    return false;
}

bool Saper::checkLeftSide(const int& x)
{
    if (x - 1 >= 0 && board[x - 1].value != 9 && (x % 10 != 0))
        return true;
    return false;
}

bool Saper::checkTopSide(const int& x)
{
    if (x - 10 >= 0 && board[x - 10].value != 9 && x > 9)
        return true;
    return false;
}

bool Saper::checkTopLeftSide(const int& x)
{
    if (x - 11 >= 0 && board[x - 11].value != 9 && (x % 10 != 0) && x > 9)
        return true;
    return false;
}

bool Saper::checkTopRightSide(const int& x)
{
    if (x - 9 >= 0 && board[x - 9].value != 9 && ((x + 1) % 10 != 0) && x > 9)
        return true;
    return false;
}

bool Saper::checkDownSide(const int& x)
{
    if (x + 10 < 100 && board[x + 10].value != 9 && x < 90)
        return true;
    return false;
}

bool Saper::checkDownLeftSide(const int& x)
{
    if (x + 9 < 100 && board[x + 9].value != 9 && (x % 10 != 0) && x < 90)
        return true;
    return false;
}

bool Saper::checkDownRightSide(const int& x)
{
    if (x + 11 < 100 && board[x + 11].value != 9 && ((x + 1) % 10 != 0) && x < 90)
        return true;
    return false;
}






