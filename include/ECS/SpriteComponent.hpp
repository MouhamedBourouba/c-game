#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
#include "ECS/ECS.hpp"
#include "ECS/PositionComponent.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#pragma once

class SpriteComponent : public Component {
private:
  PositionComponent posComp() {
    return entity->getComponent<PositionComponent>();
  };
  SDL_Texture *texture;
  SDL_Rect src, dst;

public:
  SpriteComponent() = default;

  SpriteComponent(const char *filePath) {
    texture = TextureManager::loadTexture(filePath);
  }

  void init() override {
    src.x = src.y = 0;
    dst.x = dst.y = 0;
    src.w = src.h = 32;
    dst.w = dst.h = 64;
  }

  void draw() override { TextureManager::draw(texture, &src, &dst); }

  void update() override {
    dst.x = posComp().getXPos();
    dst.y = posComp().getYPos();
  }
};

#endif
