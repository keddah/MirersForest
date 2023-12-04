#pragma once
#include "SpriteRenderer.h"

class Tile
{
public:
    Tile(const std::string& filePath, Vector2 position);

    ManualRenderer& GetRenderer() { return renderer; }
    
private:
    Vector2 pos;
    ManualRenderer renderer;
};
