#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#pragma once

class Game
{
public:
    Game();
    ~Game();
    void init(const char *title, int xpos, int ypos, int width, int hight, bool fullscreen);
    void update();
    void handleEvent();
    void render();
    void clean();
    bool running() { return isRunning; }

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif