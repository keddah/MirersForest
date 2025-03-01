/**************************************************************************************************************
* Tile - Header
*
* The header file for the Tile class. Its renderer is given its texture from its manager so that there isn't a need for a unique texture for each tile. Supplies functions
* that the tile manager will need to maintain each tile in the level.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#pragma once
#include "Renderers.h"

class Tile
{
public:
    Tile(SDL_Texture* tex, Vector2 pos, SDL_Rect source, int tileSize, bool isFinish = false);
    
    const ManualRenderer& GetRenderer() const { return renderer; }
    void Draw() { renderer.Draw(); }
    void Destroy() { renderer.DestroyAllTextures(); }
    
    const SDL_FRect& GetRect() const { return { position.x, position.y, renderer.GetRect().w, renderer.GetRect().h }; }
    
    const Vector2& GetPosition() const { return position; }
    void SetPosition(const Vector2 pos) { position = pos; renderer.SetPosition(pos); }
    bool IsFinishLine() const { return finishLine; }
    
    short GetLevelSlide() const { return levelSlide; }
    void SetSlide(const short slide) { levelSlide = slide; }
    
private:
    Vector2 position;
    ManualRenderer renderer;
    
    short levelSlide = 0;
    bool finishLine;
};
