#include "game.h"


int main()
{
    //set random by time
    srand(static_cast<unsigned>(time(nullptr)));


    Game game;
    game.run();

    return 0;
}

