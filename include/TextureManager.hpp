#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#pragma once

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();
    static void draw(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dst);
    static SDL_Texture *loadTexture(const char *texturePath);
};

#endif