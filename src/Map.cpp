#include "Map.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"

Map::Map()
{
    ground = TextureManager::loadTexture("resource/dirt.png");
    sky = TextureManager::loadTexture("resource/sky.png");
    grass = TextureManager::loadTexture("resource/grass.png");
    src.x = src.y = 0;
    dst.x = dst.y = 0;
    dst.w = src.w = 32;
    src.h = dst.h = 32;
}
Map::~Map() {}

void Map::loadMap(int arr[20][25])
{
    for (int row = 0; row < 20; row++)
    {
        for (int column = 0; column < 25; column++)
        {
            currentMap[row][column] = arr[row][column];
        }
    }
}

void Map::drawMap()
{
    for (int row = 0; row < 20; row++)
    {
        for (int column = 0; column < 25; column++)
        {
            dst.x = 32 * column;
            dst.y = 32 * row;

            switch (currentMap[row][column])
            {
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
