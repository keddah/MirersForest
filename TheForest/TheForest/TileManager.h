/**************************************************************************************************************
* Tile Manager - Header
*
* The header file for the Tile manager class. Declares all of the functions and parameters that the tile manager needs to create the tiles for each level
* in the game.
* Also creates source rectangles to be used for the different placeable tiles from the tile sheet that is created in each tile object.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#pragma once
#include <vector>

#include "Tile.h"

class TileManager
{
public:
    TileManager() = default;
    void Draw();
    
    std::vector<Tile>& GetTiles() { return tiles; }
    
    void MakeTiles(short lvlIndex, bool reset = false);
    void SetLevelSlide(short slide);
    void Reset();

private:
    static constexpr short tileSize = 16;
    
    // The source rectangles for some of the different textures in the tile sheet
    const SDL_Rect stoneDirt1 {0,0, tileSize, tileSize};
    const SDL_Rect stoneDirt2 {tileSize * 2,0, tileSize, tileSize};
    const SDL_Rect lightishStone {tileSize * 9,0, tileSize, tileSize};
    const SDL_Rect darkStone1 {tileSize * 8,tileSize, tileSize, tileSize};
    const SDL_Rect darkStone2 {tileSize * 9,tileSize, tileSize, tileSize};
    const SDL_Rect darkStone3 {tileSize * 10,tileSize, tileSize, tileSize};
    const SDL_Rect hardDarkStone {tileSize * 6,tileSize, tileSize, tileSize};
    const SDL_Rect softDarkStone {tileSize * 11,tileSize, tileSize, tileSize};
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
    const SDL_Rect end1 {tileSize * 3,tileSize * 22, tileSize, tileSize};
    const SDL_Rect end2 {tileSize * 2,tileSize * 22, tileSize, tileSize};
    const SDL_Rect invisible {tileSize * 16, 0, tileSize, tileSize};

    short levelSlide = 0;
    std::vector<Tile> tiles;

    void Level1Tiles();
    void Level2Tiles();
};
