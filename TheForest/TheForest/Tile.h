#pragma once
#include "SpriteRenderer.h"
#include "Vector2.h"

class Tile
{
public:
    Tile(const std::string& filePath, Vector2 position);

    SpriteRenderer& GetRenderer() { return renderer; }
    
private:
    Vector2 pos;
    SpriteRenderer renderer = SpriteRenderer("", pos);
};
