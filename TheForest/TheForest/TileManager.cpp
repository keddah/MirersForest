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
        tile.SetPosition({tile.GetPosition().x + (next? -GameWindow::GetWindowWidth() * slide: GameWindow::GetWindowWidth()), tile.GetPosition().y});
    }
    
    levelSlide = slide;
}

void TileManager::Level1Tiles()
{
    float start = -400;
    Vector2 spawnPos = Vector2(start, tileSize * 64);


    //\\//\\//\\//\\// 1st Slide //\\//\\//\\//\\// 
    // for(short darkCols = 0; darkCols < 4; darkCols++)
    // {
    //     for(short darkRow = 0; darkRow < 140; darkRow++)
    //     {
    //         Tile newTile = Tile(tileSheet, spawnPos, darkDirt2, tileSize);
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
    //         Tile newTile = Tile(tileSheet, spawnPos, dirt2, tileSize);
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
    //     Tile newTile = Tile(tileSheet, spawnPos, grassDirt2, tileSize);
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

    spawnPos = Vector2(1516 + GameWindow::GetWindowWidth(), 660);
    for(short i = 0; i < 22; i++)
    {
        Tile newTile = Tile(tileSheet, spawnPos, wood, tileSize);

        tiles.emplace_back(newTile);

        spawnPos.x += i % 2 == 0? 0 : tileSize;
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(1716 + GameWindow::GetWindowWidth(), 750);
    for(short i = 0; i < 22; i++)
    {
        Tile newTile = Tile(tileSheet, spawnPos, wood, tileSize);

        tiles.emplace_back(newTile);

        spawnPos.x += i % 2 == 0? 0 : tileSize;
        spawnPos.y -= i % 3 == 0? 0 : tileSize;
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

    spawnPos = Vector2(1600 + GameWindow::GetWindowWidth(), 300);
    for(short hori = 0; hori < 10; hori++)
    {
        for(short vert = 0; vert < 15; vert++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(tileSheet, spawnPos, rnd == 1? leaves2 : leaves1, tileSize);

            tiles.emplace_back(newTile);

            spawnPos.x += tileSize;
        }
        spawnPos.x = 1650 + GameWindow::GetWindowWidth();
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(1800 + GameWindow::GetWindowWidth(), 400);
    for(short hori = 0; hori < 10; hori++)
    {
        for(short i = 0; i < 20; i++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(tileSheet, spawnPos, rnd == 1? leaves2 : leaves1, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1800 + GameWindow::GetWindowWidth() - tileSize * hori * 2;
        spawnPos.y -= tileSize;
    }

    spawnPos = Vector2(1700 + GameWindow::GetWindowWidth(), 600);
    for(short hori = 0; hori < 10; hori++)
    {
        for(short i = 0; i < 20; i++)
        {
            const short rnd = rand() % 2;
            if(i > 5 && i > 15)
            {
                Tile newTile = Tile(tileSheet, spawnPos, rnd == 1? leaves2 : leaves1, tileSize);
                tiles.emplace_back(newTile);
            }
            
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1700 + GameWindow::GetWindowWidth() - tileSize * hori * 2;
        spawnPos.y -= tileSize;
    }

    spawnPos = Vector2(1770 + GameWindow::GetWindowWidth(), 460);
    for(short hori = 0; hori < 5; hori++)
    {
        for(short vert = 0; vert < 10; vert++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(tileSheet, spawnPos, rnd == 1? leaves2 : leaves1, tileSize);

            tiles.emplace_back(newTile);

            spawnPos.x += tileSize;
        }
        spawnPos.x = 1810 + GameWindow::GetWindowWidth();
        spawnPos.y += tileSize;
    }

    //\\//\\//\\//\\// 3rd Slide //\\//\\//\\//\\// 

    start = GameWindow::GetWindowWidth() * 2 + 600;
    spawnPos = Vector2(start, tileSize * 64);
    for(short darkCols = 0; darkCols < 4; darkCols++)
    {
        for(short darkRow = 0; darkRow < 80; darkRow++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, darkDirt1, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(start, tileSize * 60);
    for(short stoneCols = 0; stoneCols < 4; stoneCols++)
    {
        for(short stoneRows = 0; stoneRows < 80; stoneRows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, stoneDirt2, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(start, tileSize * 56);
    for(short dirtCols = 0; dirtCols < 4; dirtCols++)
    {
        for(short dirtRows = 0; dirtRows < 80; dirtRows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, dirt2, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(start, tileSize * 55);
    for(short grass = 0; grass < 80; grass++)
    {
        Tile newTile = Tile(tileSheet, spawnPos, grassDirt2, tileSize);
    
        tiles.emplace_back(newTile);
    
        spawnPos.x += tileSize;
    }
    
    spawnPos = Vector2(1200 + GameWindow::GetWindowWidth() * 2, 732);
    for(short dirtCols = 0; dirtCols < 10; dirtCols++)
    {
        for(short dirtRows = 0; dirtRows < 20; dirtRows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, dirt1, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1200 + GameWindow::GetWindowWidth() * 2;
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(1510 + GameWindow::GetWindowWidth() * 2, 716);
    for(short i = 0; i < 31; i++)
    {
        Tile newTile = Tile(tileSheet, spawnPos, stone1, tileSize);

        tiles.emplace_back(newTile);

        spawnPos.x += i % 10 == 0? tileSize : 0;
        spawnPos.y -=tileSize;
    }

    spawnPos = Vector2(1400 + GameWindow::GetWindowWidth() * 2, 210);
    for(short cols = 0; cols < 2; cols++)
    {
        for(short rows = 0; rows < 12; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1400 + GameWindow::GetWindowWidth() * 2;
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(1880 + GameWindow::GetWindowWidth() * 2, 210);
    for(short cols = 0; cols < 2; cols++)
    {
        for(short rows = 0; rows < 12; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1880 + GameWindow::GetWindowWidth() * 2;
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(700 + GameWindow::GetWindowWidth() * 2, 0);
    for(short cols = 0; cols < 30; cols++)
    {
        for(short rows = 0; rows < 6; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 700 + GameWindow::GetWindowWidth() * 2;
        spawnPos.y += tileSize;
    }

    start = spawnPos.x;
    spawnPos = Vector2(start, spawnPos.y);
    for(short cols = 0; cols < 2; cols++)
    {
        for(short rows = 0; rows < 20; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }


    //\\//\\//\\//\\// 4th Slide //\\//\\//\\//\\// 

    spawnPos = Vector2(200 + GameWindow::GetWindowWidth() * 3, 600);
    for(short cols = 0; cols < 2; cols++)
    {
        for(short rows = 0; rows < 12; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 200 + GameWindow::GetWindowWidth() * 3;
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(700 + GameWindow::GetWindowWidth() * 3, 600);
    for(short cols = 0; cols < 2; cols++)
    {
        for(short rows = 0; rows < 6; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 200 + GameWindow::GetWindowWidth() * 3;
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(980 + GameWindow::GetWindowWidth() * 3, 400);
    for(short rows = 0; rows < 6; rows++)
    {
        Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);

        tiles.emplace_back(newTile);

        spawnPos.x += tileSize;
    }

    spawnPos = Vector2(1800 + GameWindow::GetWindowWidth() * 3, 900);
    for(short cols = 0; cols < 2; cols++)
    {
        for(short rows = 0; rows < 16; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1800 + GameWindow::GetWindowWidth() * 3;
        spawnPos.y += tileSize;
    }


    //\\//\\//\\//\\// 5th Slide //\\//\\//\\//\\//
    
    spawnPos = Vector2(320 + GameWindow::GetWindowWidth() * 4, 1030);
    for(short cols = 0; cols < 4; cols++)
    {
        for(short rows = 0; rows < 100; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 320 + GameWindow::GetWindowWidth() * 4;
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(1000 + GameWindow::GetWindowWidth() * 4, 1030);
    for(short cols = 0; cols < 15; cols++)
    {
        for(short rows = 0; rows < 20; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1000 + GameWindow::GetWindowWidth() * 4;
        spawnPos.y -= tileSize;
    }

    start = spawnPos.x + tileSize * 20;
    spawnPos = Vector2(start, spawnPos.y - tileSize * 15);
    for(short cols = 0; cols < 32; cols++)
    {
        for(short rows = 0; rows < 20; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }

    start = spawnPos.x + tileSize * 20;
    spawnPos = Vector2(start, 1030);
    for(short cols = 0; cols < 15; cols++)
    {
        for(short rows = 0; rows < 25; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y -= tileSize;
    }


    //\\//\\//\\//\\// 6th Slide //\\//\\//\\//\\//

    spawnPos = Vector2(400 + GameWindow::GetWindowWidth() * 5, 1000);
    for(short cols = 0; cols < 6; cols++)
    {
        for(short rows = 0; rows < 16; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 400 + GameWindow::GetWindowWidth() * 5;
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(600 + GameWindow::GetWindowWidth() * 5, 1000);

    for(short cols = 0; cols < 6; cols++)
    {
        for(short rows = 0; rows < 4; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
        
            tiles.emplace_back(newTile);
        
            spawnPos.x += tileSize;
        }
        spawnPos.x = 600 + GameWindow::GetWindowWidth() * 5;
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(800 + GameWindow::GetWindowWidth() * 5, 1000);
    for(short cols = 0; cols < 6; cols++)
    {
        for(short rows = 0; rows < 4; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 800 + GameWindow::GetWindowWidth() * 5;
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(1000 + GameWindow::GetWindowWidth() * 5, 1000);
    for(short cols = 0; cols < 6; cols++)
    {
        for(short rows = 0; rows < 4; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1000 + GameWindow::GetWindowWidth() * 5;
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(1600 + GameWindow::GetWindowWidth() * 5, 800);
    for(short cols = 0; cols < 18; cols++)
    {
        for(short rows = 0; rows < 4; rows++)
        {
            Tile newTile = Tile(tileSheet, spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1600 + GameWindow::GetWindowWidth() * 5;
        spawnPos.y += tileSize;
    }
}
