#pragma once
#define print(x) { std::cout<< x << std::endl; }


#include <vector>

#include "Tile.h"

class TileManager
{
public:
    TileManager();

    std::vector<Tile>& GetTiles() { return tiles; }
    
    void MakeTiles();

private:
    static constexpr short tileSize = 16;
    Tile test = Tile("TileSets/test16-16.jpg", Vector2(100, 500));

    // Level layout (the formation of the tiles within the level)
    short tileSet[100][20];
    
    std::vector<Tile> tiles;
};
