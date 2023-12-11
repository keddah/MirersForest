#pragma once
#include "Renderers.h"

class Tile
{
public:
    Tile(const std::string& filePath, Vector2 position, SDL_Rect sourceRect, int tileSize);

    const ManualRenderer& GetRenderer() const { return renderer; }
    void Scroll(bool next);
    
private:
    std::string spritePath;
    Vector2 pos;
    ManualRenderer renderer;
};
