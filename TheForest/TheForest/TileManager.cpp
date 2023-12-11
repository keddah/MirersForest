#include "TileManager.h"

#include "GameSingletons.h"

TileManager::TileManager()
{
    //tiles.push_back(test);
    //MakeTiles();
}

// Make a tile Renderer so that the position doesn't have to be a reference

void TileManager::MakeTiles(short lvlIndex)
{
    constexpr float start = -100;
    Vector2 grassPos = Vector2(start, 800);
    Vector2 platform = Vector2(2500, 500);

    Vector2 dirtPos = Vector2(start, grassPos.y - tileSize);
    
    // Grass
    // for (int i = 0; i < 200; i++)
    // {
    //     Tile newTile = Tile(tileSheet, grassPos, grassDirt1, tileSize);
    //
    //     tiles.emplace_back(newTile);
    //
    //     grassPos.x += tileSize;
    // }
    
    for (int rows = 0; rows < 10; rows++)
    {
        for(int column = 0; column < 500; column++)
        {
            Tile newTile = Tile(tileSheet, dirtPos, rows == 0? grassDirt1: dirt1, tileSize);

            tiles.emplace_back(newTile);

            dirtPos.x += tileSize;
        }
        dirtPos.x = start;
        dirtPos.y += tileSize;
    }

    for (int i = 0; i < 16; i++)
    {
        Tile newTile = Tile("TileSets/test16-16.jpg", platform, stone1, tileSize);
    
        tiles.emplace_back(newTile);
    
        platform.x += tileSize;
    }

    // Vector2 startPos = Vector2(0, 400);
    // for (int h = 0; h < levelWidth + 50; h++)
    // {
    //     Tile newTile = Tile("TileSets/test16-16.jpg", startPos);
    //
    //     tiles.emplace_back(newTile);
    //
    //     startPos.x += tileSize;
    // }

    // Adding the tile to the correct slide
    SDL_GetWindowSize(GameWindow::GetWindow(), &screenWidth, nullptr);
    for (auto& tile : tiles)
    {
        tile.SetSlide(floor(tile.GetPosition().x / screenWidth));
        // tile.SetSlide(static_cast<short>(round(tile.GetPosition().x / screen)));
    }
}

void TileManager::SetLevelSlide(short slide)
{
    if(slide == levelSlide) return;
    
    const bool next = slide > levelSlide;
    
    for (auto& tile : tiles)
    {
        tile.SetPosition({tile.GetPosition().x + (next? -screenWidth : screenWidth), tile.GetPosition().y});
        tile.SetSlide(slide);
    }
    levelSlide = slide;
}
