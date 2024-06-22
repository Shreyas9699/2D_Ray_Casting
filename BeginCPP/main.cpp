#include "include/Game.h"

int main()
{
    Game game(1280, 700, "res/shapesConfig.txt");
    game.run();
    return 0;
}