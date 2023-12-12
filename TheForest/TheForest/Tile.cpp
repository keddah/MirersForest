#include "Tile.h"

Tile::Tile(const std::string& filePath, Vector2 pos, SDL_Rect source, int tileSize): position(pos), renderer(filePath, pos)
{
    spritePath = filePath;
    renderer.FromTileSheet(source, tileSize);
}
