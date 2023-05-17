#include "Game.hpp"
#include "ECS/ECS.hpp"
#include "ECS/PositionComponent.hpp"
#include "ECS/SpriteComponent.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <iostream>

SDL_Renderer *Game::renderer;

Game::Game(GameInfo gameInfo)
    : gameInfo(gameInfo), isRunning(true), map(Map()), manager(Manager()),
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
  if (gameInfo.fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "Feild to init sdl: " << SDL_GetError() << std::endl;
    return (false);
  }

  mWindow = SDL_CreateWindow(gameInfo.title, gameInfo.xpos, gameInfo.ypos,
                             gameInfo.width, gameInfo.hight, flags);
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

    default:
      break;
    }
  }
}
