#include "TextureManager.hpp"
#include "Game.hpp"

TextureManager::TextureManager() {}
TextureManager::~TextureManager() {}

void TextureManager::draw(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dst)
{
    SDL_RenderCopy(Game::renderer, texture, src, dst);
}

SDL_Texture* TextureManager::loadTexture(const char *texturePath)
{
    return IMG_LoadTexture(Game::renderer, texturePath);
}
