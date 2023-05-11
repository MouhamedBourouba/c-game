#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
#include <SDL2/SDL.h>

#pragma once

class RenderManager
{
public:
    RenderManager();
    ~RenderManager();
    void createMainWindow(char *title);
    SDL_Texture* loadTexture(char *filePath);
    void render(SDL_Texture* texture);
    void quit();

private:
    SDL_Window *p_window;
    SDL_Renderer *p_renderer;
};

#endif