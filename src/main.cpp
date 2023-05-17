#include "Game.hpp"
#include <iostream>

int MAX_FPS = 60;

int main(int argv, char *args[]) {
  
  Game *game = new Game();
  game->run(MAX_FPS);

  return (0);
}
