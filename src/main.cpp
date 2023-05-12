#include <iostream>
#include <memory>
#include <SDL2/SDL.h>

#include "Game.hpp"

Game *game = nullptr;

int main(int argv, char *args[])
{
    game = new Game();
    game->init("HOLY SMOKES", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while (game->running())
    {
        game->handleEvent();
        game->update();
        game->render();
    }

    return 0;
}