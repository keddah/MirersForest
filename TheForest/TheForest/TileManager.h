#pragma once
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

    // The start position can't be a local variable because the sprite renderer uses this position as a reference

    static constexpr int levelWidth = 100;
    static constexpr int levelHeight = 20;

    // Level layout (the formation of the tiles within the level)
    short tileSet[levelWidth][levelHeight];
    
    std::vector<Tile> tiles;
};
