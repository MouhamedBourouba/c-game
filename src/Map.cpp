#include "Map.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"

Map::Map() {}
Map::~Map() {}

void Map::init() {
  ground = TextureManager::loadTexture("resources/dirt.png");
  sky = TextureManager::loadTexture("resources/sky.png");
  grass = TextureManager::loadTexture("resources/grass.png");
  src.x = src.y = 0;
  dst.x = dst.y = 0;
  dst.w = src.w = 32;
  src.h = dst.h = 32;
}

void Map::loadMap(int arr[20][25]) {
  for (int row = 0; row < 20; row++) {
    for (int column = 0; column < 25; column++) {
      currentMap[row][column] = arr[row][column];
    }
  }
}

void Map::drawMap() {
  for (int row = 0; row < 20; row++) {
    for (int column = 0; column < 25; column++) {
      dst.x = 32 * column;
      dst.y = 32 * row;

      switch (currentMap[row][column]) {
      case 0:
        TextureManager::draw(sky, &src, &dst);
        break;
      case 1:
        TextureManager::draw(grass, &src, &dst);
        break;
      case 2:
        TextureManager::draw(ground, &src, &dst);
        break;
      default:
        break;
      }
    }
  }
}
