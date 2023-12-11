#include "Tile.h"

#include "GameSingletons.h"

Tile::Tile(const std::string& filePath, Vector2 position, SDL_Rect sourceRect, int tileSize): pos(position), renderer(filePath, pos)
{
    spritePath = filePath;
    renderer.FromTileSheet(sourceRect, tileSize);
}

void Tile::Scroll(bool next)
{
    int screenWidth;
    SDL_GetWindowSize(GameWindow::GetWindow(), &screenWidth, NULL);

    pos.x += next? screenWidth : -screenWidth;

    renderer = ManualRenderer(spritePath, pos);
}
