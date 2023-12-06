#pragma once
#include "SpriteRenderer.h"

class Tile
{
public:
    Tile(const std::string& filePath, Vector2 position, SDL_Rect sourceRect, int tileSize);

    ManualRenderer& GetRenderer() { return renderer; }
    
private:
    Vector2 pos;
    ManualRenderer renderer;
};
