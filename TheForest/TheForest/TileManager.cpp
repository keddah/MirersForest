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
    Vector2 grassPos = Vector2(-500, 800);
    Vector2 platform = Vector2(800, 500);


    Vector2 dirtPos = Vector2(-500, grassPos.y - tileSize);
    
    // Grass
    for (int i = 0; i < 200; i++)
    {
        Tile newTile = Tile(tileSheet, grassPos, grassDirt1, tileSize);
    
        tiles.emplace_back(newTile);
    
        grassPos.x += tileSize;
    }
    
    for (int rows = 0; rows < 10; rows++)
    {
        for(int column = 0; column < 1000; column++)
        {
            Tile newTile = Tile(tileSheet, dirtPos, rows == 0? grassDirt1: dirt1, tileSize);

            tiles.emplace_back(newTile);

            dirtPos.x += tileSize;
        }
        dirtPos.y += tileSize;
    }

    // Vector2 pillar2 = Vector2(1900, 400);
    // for (int i = 0; i < 5; i++)
    // {
    //     Tile newTile = Tile("TileSets/test16-16.jpg", pillar2);
    //
    //     tiles.emplace_back(newTile);
    //
    //     pillar2.y -= tileSize;
    // }

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
    int screen;
    SDL_GetWindowSize(GameWindow::GetWindow(), &screen, NULL);
    for (auto& tile : tiles)
    {
        tile.SetSlide(floor(tile.GetPosition().x / screen));
        // tile.SetSlide(static_cast<short>(round(tile.GetPosition().x / screen)));
    }
}