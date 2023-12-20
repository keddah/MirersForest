#pragma once
#include <vector>

#include "Tile.h"

class TileManager
{
public:
    TileManager();
    void Draw();
    
    std::vector<Tile>& GetTiles() { return tiles; }
    
    void MakeTiles(short lvlIndex);
    void SetLevelSlide(short slide);
    
private:
    static constexpr short tileSize = 16;
    
    // The source rectangles for some of the different textures in the tile sheet
    const SDL_Rect stoneDirt1 {0,0, tileSize, tileSize};
    const SDL_Rect stoneDirt2 {tileSize * 2,0, tileSize, tileSize};
    const SDL_Rect stone1 {tileSize * 9,0, tileSize, tileSize};
    const SDL_Rect stone2 {tileSize * 9,tileSize, tileSize, tileSize};
    const SDL_Rect leaves1 {0,tileSize * 16, tileSize, tileSize};
    const SDL_Rect leaves2 {tileSize,tileSize * 16, tileSize, tileSize};
    const SDL_Rect grassDirt1 {tileSize * 2,tileSize * 29, tileSize, tileSize};
    const SDL_Rect grassDirt2 {tileSize * 3,tileSize * 29, tileSize, tileSize};
    const SDL_Rect dirt1 {tileSize * 2,tileSize * 30, tileSize, tileSize};
    const SDL_Rect dirt2 {tileSize * 3,tileSize * 30, tileSize, tileSize};
    const SDL_Rect darkDirt1 {tileSize,tileSize * 30, tileSize, tileSize};
    const SDL_Rect darkDirt2 {tileSize * 5,tileSize * 30, tileSize, tileSize};
    const SDL_Rect wood {tileSize * 13,tileSize * 12, tileSize, tileSize};
    const SDL_Rect platform {tileSize * 16,tileSize * 24, tileSize, tileSize};

    const std::string tileSheet = "TileSets/Textures-16.png"; 
    
    // The start position can't be a local variable because the sprite renderer uses this position as a reference

    static constexpr int levelWidth = 100;
    static constexpr int levelHeight = 20;

    // Level layout (the formation of the tiles within the level)
    short tileSet[levelWidth][levelHeight];

    short levelSlide;
    std::vector<Tile> tiles;

    // Vector2 screenSize;
    void Level1Tiles();
};
