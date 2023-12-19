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
    switch (lvlIndex)
    {
        case 0:
            Level1Tiles();
            break;

        default:
            Level1Tiles();
            break;
    }

    for (auto& tile : tiles)
    {
        tile.SetSlide(floor(tile.GetPosition().x / GameWindow::GetWindowWidth()));
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
        tile.SetPosition({tile.GetPosition().x + (next? -GameWindow::GetWindowWidth() : GameWindow::GetWindowWidth()), tile.GetPosition().y});
    }
    
    levelSlide = slide;
}

void TileManager::Level1Tiles()
{
    constexpr float start = -400;
    Vector2 spawnPos = Vector2(start, tileSize * 64);


    //\\//\\//\\//\\// 1st Slide //\\//\\//\\//\\// 
    // for(short darkCols = 0; darkCols < 4; darkCols++)
    // {
    //     for(short darkRow = 0; darkRow < 140; darkRow++)
    //     {
    //         Tile newTile = Tile(tileSheet, spawnPos, darkDirt1, tileSize);
    //
    //         tiles.emplace_back(newTile);
    //
    //         spawnPos.x += tileSize;
    //     }
    //     spawnPos.x = start;
    //     spawnPos.y += tileSize;
    // }
    //
    // spawnPos = Vector2(start, tileSize * 60);
    // for(short stoneCols = 0; stoneCols < 4; stoneCols++)
    // {
    //     for(short stoneRows = 0; stoneRows < 140; stoneRows++)
    //     {
    //         Tile newTile = Tile(tileSheet, spawnPos, stoneDirt2, tileSize);
    //
    //         tiles.emplace_back(newTile);
    //
    //         spawnPos.x += tileSize;
    //     }
    //     spawnPos.x = start;
    //     spawnPos.y += tileSize;
    // }
    //
    // spawnPos = Vector2(start, tileSize * 56);
    // for(short dirtCols = 0; dirtCols < 4; dirtCols++)
    // {
    //     for(short dirtRows = 0; dirtRows < 140; dirtRows++)
    //     {
    //         Tile newTile = Tile(tileSheet, spawnPos, dirt1, tileSize);
    //
    //         tiles.emplace_back(newTile);
    //
    //         spawnPos.x += tileSize;
    //     }
    //     spawnPos.x = start;
    //     spawnPos.y += tileSize;
    // }
    //
    // spawnPos = Vector2(start, tileSize * 55);
    // for(short grass = 0; grass < 140; grass++)
    // {
    //     Tile newTile = Tile(tileSheet, spawnPos, grassDirt1, tileSize);
    //
    //     tiles.emplace_back(newTile);
    //
    //     spawnPos.x += tileSize;
    // }
    //
    //
    // Vector2 treeTrunk = Vector2(1200 + 30 * tileSize, spawnPos.y + tileSize);
    // for(short hori = 0; hori < 4; hori++)
    // {
    //     for(short vert = 0; vert < 40; vert++)
    //     {
    //         Tile newTile = Tile(tileSheet, treeTrunk, wood, tileSize);
    //
    //         tiles.emplace_back(newTile);
    //
    //         treeTrunk.y -= tileSize;
    //     }
    //     treeTrunk.y = spawnPos.y + tileSize;
    //     treeTrunk.x += tileSize;
    // }
    //
    // spawnPos = Vector2(1200, 400);
    // for(short hori = 0; hori < 10; hori++)
    // {
    //     for(short i = 0; i < 30; i++)
    //     {
    //         const short rnd = rand() % 2;
    //         Tile newTile = Tile(tileSheet, spawnPos, rnd == 1? leaves1 : leaves2, tileSize);
    //
    //         tiles.emplace_back(newTile);
    //
    //         spawnPos.x += tileSize;
    //     }
    //     spawnPos.x = 1200 + tileSize * hori  * 3;
    //     spawnPos.y += tileSize;
    // }
    //
    // spawnPos = Vector2(1600, 400);
    // for(short hori = 0; hori < 10; hori++)
    // {
    //     for(short i = 0; i < 30; i++)
    //     {
    //         const short rnd = rand() % 2;
    //         Tile newTile = Tile(tileSheet, spawnPos, rnd == 1? leaves2 : leaves1, tileSize);
    //
    //         tiles.emplace_back(newTile);
    //
    //         spawnPos.x += tileSize;
    //     }
    //     spawnPos.x = 1600 + tileSize * hori;
    //     spawnPos.y -= tileSize;
    // }
    //
    // spawnPos = Vector2(1800, 400);
    // for(short hori = 0; hori < 10; hori++)
    // {
    //     for(short i = 0; i < 30; i++)
    //     {
    //         const short rnd = rand() % 2;
    //         Tile newTile = Tile(tileSheet, spawnPos, rnd == 1? leaves2 : leaves1, tileSize);
    //
    //         tiles.emplace_back(newTile);
    //
    //         spawnPos.x += tileSize;
    //     }
    //     spawnPos.x = 1800 - tileSize * hori * 2;
    //     spawnPos.y -= tileSize;
    // }
    //
    // spawnPos = Vector2(1900, 300);
    // for(short hori = 0; hori < 10; hori++)
    // {
    //     for(short i = 0; i < 30; i++)
    //     {
    //         const short rnd = rand() % 2;
    //         Tile newTile = Tile(tileSheet, spawnPos, rnd == 1? leaves2 : leaves1, tileSize);
    //
    //         tiles.emplace_back(newTile);
    //
    //         spawnPos.x += tileSize;
    //     }
    //     spawnPos.x = 1900 + tileSize * hori + tileSize;
    //     spawnPos.y -= tileSize;
    // }


    //\\//\\//\\//\\// 2nd Slide //\\//\\//\\//\\// 
    spawnPos = Vector2((1200 + 30 * tileSize) + GameWindow::GetWindowWidth(), GameWindow::GetWindowHeight());
    for(short hori = 0; hori < 4; hori++)
    {
        for(short vert = 0; vert < 42; vert++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, wood, tileSize);

            tiles.emplace_back(newTile);

            spawnPos.y -= tileSize;
        }
        spawnPos.y = GameWindow::GetWindowHeight();
        spawnPos.x += tileSize;
    }

    spawnPos = Vector2(1600 + GameWindow::GetWindowWidth(), 400);
    for(short hori = 0; hori < 4; hori++)
    {
        for(short vert = 0; vert < 8; vert++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(tileSheet, spawnPos, rnd == 1? leaves2 : leaves1, tileSize);

            tiles.emplace_back(newTile);

            spawnPos.x += tileSize;
        }
        spawnPos.x = 1600 + GameWindow::GetWindowWidth();
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(1540 + GameWindow::GetWindowWidth(), 460);
    for(short hori = 0; hori < 4; hori++)
    {
        for(short vert = 0; vert < 8; vert++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(tileSheet, spawnPos, rnd == 1? leaves2 : leaves1, tileSize);

            tiles.emplace_back(newTile);

            spawnPos.x += tileSize;
        }
        spawnPos.x = 1500 + GameWindow::GetWindowWidth();
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(1616 + GameWindow::GetWindowWidth(), 350);
    for(short hori = 0; hori < 4; hori++)
    {
        for(short vert = 0; vert < 20; vert++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(tileSheet, spawnPos, rnd == 1? leaves2 : leaves1, tileSize);

            tiles.emplace_back(newTile);

            spawnPos.x += tileSize;
        }
        spawnPos.x = 1616 + GameWindow::GetWindowWidth();
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(1790 + GameWindow::GetWindowWidth(), 400);
    for(short hori = 0; hori < 4; hori++)
    {
        for(short vert = 0; vert < 20; vert++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(tileSheet, spawnPos, rnd == 1? leaves2 : leaves1, tileSize);

            tiles.emplace_back(newTile);

            spawnPos.x += tileSize;
        }
        spawnPos.x = 1790 + GameWindow::GetWindowWidth();
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(1700 + GameWindow::GetWindowWidth(), 300);
    for(short hori = 0; hori < 10; hori++)
    {
        for(short vert = 0; vert < 5; vert++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(tileSheet, spawnPos, rnd == 1? leaves2 : leaves1, tileSize);

            tiles.emplace_back(newTile);

            spawnPos.x += tileSize;
        }
        spawnPos.x = 1650 + GameWindow::GetWindowWidth();
        spawnPos.y += tileSize;
    }
}
