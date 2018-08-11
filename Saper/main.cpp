#include "Game.h"

int main()
{
    Saper saper(0, 0);

    while (1)
    {
        Sleep(20);
        saper.checkButton();
    }

    system("PAUSE");
    return 0;
}