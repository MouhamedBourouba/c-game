#pragma once

struct GameObject
{
    SDL_Rect dstRect;
    SDL_Texture *texture;
    bool grounded;
};
