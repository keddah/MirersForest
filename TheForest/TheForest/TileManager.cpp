#include "TileManager.h"

TileManager::TileManager()
{
    //tiles.push_back(test);
    //MakeTiles();
}

// Make a tile Renderer so that the position doesn't have to be a reference

void TileManager::MakeTiles()
{
        Vector2 startPos = Vector2(0, 400);
    for (int h = 0; h < levelWidth; h++)
    {
        Tile newTile = Tile("TileSets/test16-16.jpg", startPos);

        tiles.emplace_back(newTile);

        startPos.x += tileSize;
    }
}
