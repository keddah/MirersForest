#include "TileManager.h"

TileManager::TileManager()
{
    //tiles.push_back(test);
    //MakeTiles();
}

// Make a tile Renderer so that the position doesn't have to be a reference

void TileManager::MakeTiles()
{
    Vector2 startY = Vector2(500, 400);
        for (int i = 0; i < 5; i++)
        {
            Tile newTile = Tile("TileSets/test16-16.jpg", startY);
    
            tiles.emplace_back(newTile);
    
            startY.y -= tileSize;
        }

    Vector2 startPos = Vector2(0, 400);
    for (int h = 0; h < levelWidth; h++)
    {
        Tile newTile = Tile("TileSets/test16-16.jpg", startPos);

        tiles.emplace_back(newTile);

        startPos.x += tileSize;
    }

}
