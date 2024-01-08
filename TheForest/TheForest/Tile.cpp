/**************************************************************************************************************
* Tile - Code
*
* The code file for the Tile class. Selects the desired tile from the tile sheet from the source rectangle that is given
* as a parameter by the tile manager.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#include "Tile.h"

Tile::Tile(Vector2 pos, SDL_Rect source, int tileSize, const bool isFinish): position(pos), renderer("TileSets/Textures-16.png", position)
{
    renderer.FromTileSheet(source, tileSize);

    finishLine = isFinish;
}
