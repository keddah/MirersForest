#include "Tile.h"

Tile::Tile(const std::string& filePath, Vector2 position, SDL_Rect sourceRect, int tileSize): pos(position), renderer(filePath, pos)
{
    renderer.FromTileSheet(sourceRect, tileSize);
}
