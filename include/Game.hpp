#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>

#include "GameInfo.hpp"
#include "GameObject.hpp"
#include "Map.hpp"

#pragma once

class Game
{
public:
    Game(GameInfo gameInfo);
    ~Game();
    void run(int MAX_FPS);

    static SDL_Renderer* renderer;

private:
    bool initSDL();
    void update();
    bool loadMedia();
    void handleEvent();
    void render();
    void clean();
    SDL_Window *mWindow;
    GameObject mPlayer = {{0, 0, 64, 64}, nullptr, true};
    bool isRunning;
    Uint32 totalTime;
    GameInfo gameInfo;
};

#endif