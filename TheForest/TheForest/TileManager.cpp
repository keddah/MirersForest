#include "TileManager.h"

#include "GameSingletons.h"

TileManager::TileManager()
{
    //tiles.push_back(test);
    //MakeTiles();
}

void TileManager::Draw()
{
    for (auto& tile : tiles)
    {
        // Draw the tile if its on the correct slide
        if(tile.GetLevelSlide() == levelSlide) tile.Draw(); 
    }
}

// Make a tile Renderer so that the position doesn't have to be a reference

void TileManager::MakeTiles(short lvlIndex)
{
    constexpr float start = -400;
    Vector2 grassPos = Vector2(start, 800);
    Vector2 platform = Vector2(2500, 500);

    Vector2 dirtPos = Vector2(start, grassPos.y - tileSize);

    Vector2 pospos = {1800, 200};
    //// next slide 
    for (int i = 0; i < 70; i++)
    {
        Tile newTile = Tile(tileSheet, pospos, darkDirt1, tileSize);
    
        tiles.emplace_back(newTile);
    
        pospos.x += tileSize;
    }

    
    for (int rows = 0; rows < 30; rows++)
    {
        for(int column = 0; column < 20; column++)
        {
            Tile newTile = Tile(tileSheet, platform, rows == 0? grassDirt1: dirt1, tileSize);

            tiles.emplace_back(newTile);

            platform.x += tileSize;
        }
        platform.x = 2500;
        platform.y += tileSize;
    }
    
    //// Main
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

    SDL_GetWindowSize(GameWindow::GetWindow(), &screenWidth, nullptr);
    for (auto& tile : tiles)
    {
        tile.SetSlide(floor(tile.GetPosition().x / screenWidth));
    }
}

void TileManager::SetLevelSlide(short slide)
{
    // Only do anything if it's a new slide
    if(slide == levelSlide) return;

    // Going to the next area means that the inputted slide is further ahead than the current one
    const bool next = slide > levelSlide;
    for (auto& tile : tiles)
    {
        // Move every tile left/right (keeping their Y value)
        tile.SetPosition({tile.GetPosition().x + (next? -screenWidth : screenWidth), tile.GetPosition().y});
    }
    
    levelSlide = slide;
}
