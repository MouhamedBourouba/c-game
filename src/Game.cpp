#include "Game.hpp"
#include <iostream>

Game::Game() {}

Game::~Game()
{
}

void Game::init(const char *title, int xpos, int ypos, int width, int hight, bool fullscreen)
{
    int flags = 0;

    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        window = SDL_CreateWindow(title, xpos, ypos, width, hight, flags);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        isRunning = true;
    }
}
void Game::update()
{
}

void Game::handleEvent()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
        }
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    // rendering logic
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
