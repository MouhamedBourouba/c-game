#include "RenderManager.h"
#include <SDL2/SDL_image.h>

RenderManager::RenderManager()
    : p_renderer(nullptr), p_window(nullptr) {}

RenderManager::~RenderManager()
{
    free(p_window);
    free(p_renderer);
}

void RenderManager::createMainWindow(char *title)
{
    p_window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1270,
        620,
        SDL_WINDOW_SHOWN);
    p_renderer = SDL_CreateRenderer(
        p_window,
        -1,
        SDL_RENDERER_ACCELERATED);
}

void RenderManager::quit()
{
    SDL_DestroyWindow(p_window);
}

SDL_Texture* RenderManager::loadTexture(char *filePath)
{
    return IMG_LoadTexture(p_renderer, filePath);
}

void RenderManager::render(SDL_Texture *texture)
{
    SDL_RenderCopy(p_renderer, texture, NULL, NULL);
    SDL_RenderPresent(p_renderer);
    return;
}
