#include "game.hpp"

int main(void)
{
#if defined(WIN32)
    system("chcp 1252");
    system("cls");
#elif defined(UNIX)
    system("clear");
#endif
    Game game;
    game.inGame();
    return 0;
}