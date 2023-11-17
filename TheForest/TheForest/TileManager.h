#pragma once
#include "Collider.h"
#include "SpriteRenderer.h"

class Tile
{
public:
    Tile(Image img, bool solid = true);
    
private:
    Collision collider;
    SpriteRenderer renderer;
};


class TileManager
{
public:
    TileManager() = default;

private:
    SpriteSheet tileSpriteSheet;
};
