#include "Tile.h"

Tile::Tile(const std::string& filePath, Vector2 position): pos(position)
{
    renderer.ResetSprite(filePath);
}
