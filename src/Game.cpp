#include "Game.hpp"
#include "ECS/ECS.hpp"
#include "ECS/PositionComponent.hpp"
#include "ECS/SpriteComponent.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>

SDL_Renderer *Game::renderer;

Game::Game()
    : isRunning(true), map(Map()), manager(Manager()),
      player(manager.addEntity()) {}

Game::~Game() {}

bool Game::loadMedia() {
  map.init();
  player.addComponent<PositionComponent>();
  player.addComponent<SpriteComponent>("resources/charcterl.png");
  return true;
}

void Game::update() { manager.update(); }

void Game::render() {
  SDL_RenderClear(renderer);
  map.drawMap();
  manager.draw();
  SDL_RenderPresent(renderer);
}

void Game::run(int MaxFPS) {
  if (!(initSDL() && loadMedia())) {
    SDL_Log("error while init Sdl or loading media");
  }

  while (isRunning) {
    totalTime = SDL_GetTicks();
    handleEvent();
    update();
    render();
    if ((SDL_GetTicks() - totalTime) < (1000 / MaxFPS)) {
      SDL_Delay((1000 / MaxFPS) - (SDL_GetTicks() - totalTime));
    }
  };
}

bool Game::initSDL() {
  int flags = 0;
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "Feild to init sdl: " << SDL_GetError() << std::endl;
    return (false);
  }

  mWindow = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, 800, 640, 0);
  renderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

  if (mWindow == nullptr || renderer == nullptr) {
    SDL_Log("cant create window or renderer: ");
    return (false);
  }
  return (true);
}

void Game::clean() {
  SDL_DestroyWindow(mWindow);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void Game::handleEvent() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
    case SDLK_SPACE:
      player.getComponent<PositionComponent>().setXPos(player.getComponent<PositionComponent>().getXPos() + 5);
    default:
      break;
    }
  }
}
