#include "Game.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include "GameObject.hpp"
#include "Components.hpp"
#include "ECS.hpp"

SDL_Renderer *Game::renderer;
Map *map;

Manager manager;
auto &newPlayer(manager.addEntity());

Game::Game(GameInfo gameInfo) : gameInfo(gameInfo), isRunning(true) {}
Game::~Game() {}

int lvl0[20][25] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void Game::run(int MaxFPS)
{
    if (!(initSDL() && loadMedia()))
    {
        SDL_Log("error while init Sdl or loading media");
    }

    while (isRunning)
    {
        totalTime = SDL_GetTicks();
        handleEvent();
        update();
        render();
        if ((SDL_GetTicks() - totalTime) < (1000 / MaxFPS))
            SDL_Delay((1000 / MaxFPS) - (SDL_GetTicks() - totalTime));
    };
}
bool Game::initSDL()
{
    int flags = 0;
    if (gameInfo.fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Feild to init sdl: ", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(gameInfo.title, gameInfo.xpos, gameInfo.ypos, gameInfo.width, gameInfo.hight, flags);
    renderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

    if (mWindow == nullptr || renderer == nullptr)
    {
        SDL_Log("cant create window or renderer: ", SDL_GetError());
        return false;
    }
    newPlayer.addComponent<PositionComponent>();
    return true;
}

bool Game::loadMedia()
{
    map = new Map();
    mPlayer.texture = IMG_LoadTexture(renderer, "resource/charcterl.png");
    return true;
}

void Game::update()
{
    mPlayer.dstRect.x++;
    mPlayer.dstRect.y++;
    manager.update();
    std::cout << newPlayer.getComponent<PositionComponent>().getXPos() << std::endl;
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
    map->drawMap();
    SDL_RenderCopy(renderer, mPlayer.texture, NULL, &mPlayer.dstRect);
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(mPlayer.texture);
    SDL_Quit();
}
