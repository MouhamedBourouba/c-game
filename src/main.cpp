#include "Game.hpp"
#include <iostream>

Game *game    = nullptr;
int   MAX_FPS = 60;

int main(int argv, char *args[])
{
   game = new Game({ "HOLY SMOKES", SDL_WINDOWPOS_CENTERED,
                     SDL_WINDOWPOS_CENTERED, 800, 640, false });
   game->run(MAX_FPS);

   return(0);
}
