#include "Tile.h"

#include "GameSingletons.h"

Tile::Tile(const std::string& filePath, Vector2 pos, SDL_Rect source, int tileSize): position(pos), renderer(filePath, pos)
{
    spritePath = filePath;
    sourceRect = source;
    size = tileSize;

    renderer.FromTileSheet(sourceRect, size);
}

void Tile::Reset()
{
    renderer = ManualRenderer(spritePath, position);
    renderer.FromTileSheet(sourceRect, size);
}

// void Tile::Scroll(short slide)
// {
//     int screenWidth;
//     SDL_GetWindowSize(GameWindow::GetWindow(), &screenWidth, NULL);
//
//     // pos.x += next? screenWidth : -screenWidth;
//
//     renderer = ManualRenderer(spritePath, pos);
// }
