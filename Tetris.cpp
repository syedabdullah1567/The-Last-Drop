#include "game.h"

int main()
{
    bool run = MainMenu();

    if (run)
    {
        runTheGame();
    }

    system("pause");
    return 0;
}