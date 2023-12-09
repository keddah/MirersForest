#pragma once
#include "Renderers.h"

class Tile
{
public:
    Tile(const std::string& filePath, Vector2 position, SDL_Rect sourceRect, int tileSize);

    const ManualRenderer& GetRenderer() const { return renderer; }
    
private:
    Vector2 pos;
    ManualRenderer renderer;
};
