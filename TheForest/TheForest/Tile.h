/**************************************************************************************************************
* Tile - Header
*
* The header file for the Tile class. Responsible for providing its own file path for the tile sheet and supplying functions
* that the tile manager will need to maintain each tile in the level.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#pragma once
#include "Renderers.h"

class Tile
{
public:
    Tile(Vector2 pos, SDL_Rect source, int tileSize, bool isFinish = false);

    const ManualRenderer& GetRenderer() const { return renderer; }
    void Draw() { renderer.Draw(); }
    
    const Vector2& GetPosition() const { return position; }
    void SetPosition(const Vector2 pos) { position = pos; renderer.SetPosition(pos); }
    bool IsFinishLine() const { return finishLine; }
    
    short GetLevelSlide() const { return levelSlide; }
    void SetSlide(const short slide) { levelSlide = slide; }
    
private:
    const std::string tileSheet = "TileSets/Textures-16.png"; 

    Vector2 position;
    ManualRenderer renderer;
    
    short levelSlide;
    bool finishLine;
};
