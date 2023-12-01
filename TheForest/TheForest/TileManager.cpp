#include "TileManager.h"

TileManager::TileManager()
{
    //tiles.push_back(test);
    //MakeTiles();
}

// Make a tile Renderer so that the position doesn't have to be a reference

void TileManager::MakeTiles()
{
    Vector2 pillar1 = Vector2(0, 400);
    for (int i = 0; i < 5; i++)
    {
        Tile newTile = Tile("TileSets/test16-16.jpg", pillar1);

        tiles.emplace_back(newTile);

        pillar1.y -= tileSize;
    }

    Vector2 pillar2 = Vector2(1900, 400);
    for (int i = 0; i < 5; i++)
    {
        Tile newTile = Tile("TileSets/test16-16.jpg", pillar2);

        tiles.emplace_back(newTile);

        pillar2.y -= tileSize;
    }

    Vector2 startPos = Vector2(0, 400);
    for (int h = 0; h < levelWidth + 50; h++)
    {
        Tile newTile = Tile("TileSets/test16-16.jpg", startPos);

        tiles.emplace_back(newTile);

        startPos.x += tileSize;
    }

}
