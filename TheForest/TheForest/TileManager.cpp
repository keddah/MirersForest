/**************************************************************************************************************
* Tile Manager - Code
*
* The code file for the Tile manager class. Responsible for creating the tiles for the all the levels in the game. Also creates the finish line
* (since it's just an invisible tile)
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

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

void TileManager::MakeTiles(short lvlIndex, const bool reset)
{
    if(reset)
    {
        levelSlide = 0;
        tiles.clear();
    }
    
    switch (lvlIndex)
    {
        case 0:
            Level1Tiles();
            break;

        case 1:
            Level2Tiles();
            break;

        default:
            Level1Tiles();
            break;
    }

    // Set which slide each tile is supposed to be on.
    for (auto& tile : tiles) tile.SetSlide(floor((tile.GetPosition().x + tileSize * .5f) / GameWindow::GetWindowWidth()));
}

void TileManager::SetLevelSlide(short slide)
{
    // Only do anything if it's a new slide
    if(slide == levelSlide) return;

    // Going to the next area means that the inputted slide is further ahead than the current one
    const bool next = slide > levelSlide;

    // If going to the next slide... while the current slide is less than parameter slide... (otherwise opposite)
    // (Spawning on a random slide doesn't break the game)
    while(next? levelSlide < slide : levelSlide > slide)
    {
        for (auto& tile : tiles)
        {
            // Move every tile left/right (keeping their Y value)
            tile.SetPosition({tile.GetPosition().x + (next? -GameWindow::GetWindowWidth(): GameWindow::GetWindowWidth()), tile.GetPosition().y});
        }
        levelSlide += next? 1 : -1;
    }
}

// Used to move all the tiles to the position that was given when they were created.
void TileManager::Reset()
{
    while(levelSlide != 0)
    {
        for (auto& tile : tiles)
        {
            // Move every tile left/right (keeping their Y value)
            tile.SetPosition({tile.GetPosition().x + GameWindow::GetWindowWidth(), tile.GetPosition().y});
        }
        levelSlide--;
    }
}

void TileManager::Level1Tiles()
{
    float start = 0;
    Vector2 spawnPos = Vector2(start, tileSize * 64);


    //\\//\\//\\//\\// 1st Slide //\\//\\//\\//\\// 
    for(short darkCols = 0; darkCols < 4; darkCols++)
    {
        for(short darkRow = 0; darkRow < 140; darkRow++)
        {
            Tile newTile = Tile(spawnPos, darkDirt2, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(start, tileSize * 60);
    for(short stoneCols = 0; stoneCols < 4; stoneCols++)
    {
        for(short stoneRows = 0; stoneRows < 140; stoneRows++)
        {
            Tile newTile = Tile(spawnPos, stoneDirt2, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(start, tileSize * 56);
    for(short dirtCols = 0; dirtCols < 4; dirtCols++)
    {
        for(short dirtRows = 0; dirtRows < 140; dirtRows++)
        {
            Tile newTile = Tile(spawnPos, dirt2, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(start, tileSize * 55);
    for(short grass = 0; grass < 140; grass++)
    {
        const bool dirt = grass == 105 || grass == 106 || grass == 107 || grass == 108;
        Tile newTile = Tile(spawnPos, dirt? dirt2 : grassDirt2, tileSize);
    
        tiles.emplace_back(newTile);
    
        spawnPos.x += tileSize;
    }
    
    
    Vector2 treeTrunk = Vector2(1200 + 30 * tileSize, spawnPos.y - tileSize);
    for(short hori = 0; hori < 4; hori++)
    {
        for(short vert = 0; vert < 29; vert++)
        {
            Tile newTile = Tile(treeTrunk, wood, tileSize);
    
            tiles.emplace_back(newTile);
    
            treeTrunk.y -= tileSize;
        }
        treeTrunk.y = spawnPos.y - tileSize;
        treeTrunk.x += tileSize;
    }
    
    spawnPos = Vector2(1200, 400);
    for(short hori = 0; hori < 10; hori++)
    {
        for(short i = 0; i < 30; i++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd == 1? leaves1 : leaves2, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1200 + tileSize * hori  * 3;
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(1600, 400);
    for(short hori = 0; hori < 10; hori++)
    {
        for(short i = 0; i < 30; i++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd == 1? leaves2 : leaves1, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1600 + tileSize * hori;
        spawnPos.y -= tileSize;
    }
    
    spawnPos = Vector2(1800, 400);
    for(short hori = 0; hori < 10; hori++)
    {
        for(short i = 0; i < 30; i++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd == 1? leaves2 : leaves1, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1800 - tileSize * hori * 2;
        spawnPos.y -= tileSize;
    }
    
    spawnPos = Vector2(1900, 300);
    for(short hori = 0; hori < 10; hori++)
    {
        for(short i = 0; i < 30; i++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd == 1? leaves2 : leaves1, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1900 + tileSize * hori + tileSize;
        spawnPos.y -= tileSize;
    }


    //\\//\\//\\//\\// 2nd Slide //\\//\\//\\//\\// 
    spawnPos = Vector2((1200 + 30 * tileSize) + GameWindow::GetWindowWidth(), GameWindow::GetWindowHeight());
    for(short hori = 0; hori < 4; hori++)
    {
        for(short vert = 0; vert < 42; vert++)
        {
            Tile newTile = Tile(spawnPos, wood, tileSize);

            tiles.emplace_back(newTile);

            spawnPos.y -= tileSize;
        }
        spawnPos.y = GameWindow::GetWindowHeight();
        spawnPos.x += tileSize;
    }

    spawnPos = Vector2(1516 + GameWindow::GetWindowWidth(), 660);
    for(short i = 0; i < 22; i++)
    {
        Tile newTile = Tile(spawnPos, wood, tileSize);

        tiles.emplace_back(newTile);

        spawnPos.x += i % 2 == 0? 0 : tileSize;
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(1716 + GameWindow::GetWindowWidth(), 750);
    for(short i = 0; i < 22; i++)
    {
        Tile newTile = Tile(spawnPos, wood, tileSize);

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
            Tile newTile = Tile(spawnPos, rnd == 1? leaves2 : leaves1, tileSize);

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
            Tile newTile = Tile(spawnPos, rnd == 1? leaves2 : leaves1, tileSize);

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
            Tile newTile = Tile(spawnPos, rnd == 1? leaves2 : leaves1, tileSize);

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
            Tile newTile = Tile(spawnPos, rnd == 1? leaves2 : leaves1, tileSize);

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
            Tile newTile = Tile(spawnPos, rnd == 1? leaves2 : leaves1, tileSize);

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
            Tile newTile = Tile(spawnPos, rnd == 1? leaves2 : leaves1, tileSize);

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
            Tile newTile = Tile(spawnPos, rnd == 1? leaves2 : leaves1, tileSize);
    
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
                Tile newTile = Tile(spawnPos, rnd == 1? leaves2 : leaves1, tileSize);
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
            Tile newTile = Tile(spawnPos, rnd == 1? leaves2 : leaves1, tileSize);

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
            Tile newTile = Tile(spawnPos, darkDirt1, tileSize);
    
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
            Tile newTile = Tile(spawnPos, stoneDirt2, tileSize);
    
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
            Tile newTile = Tile(spawnPos, dirt2, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(start, tileSize * 55);
    for(short grass = 0; grass < 80; grass++)
    {
        Tile newTile = Tile(spawnPos, grassDirt2, tileSize);
    
        tiles.emplace_back(newTile);
    
        spawnPos.x += tileSize;
    }
    
    spawnPos = Vector2(1200 + GameWindow::GetWindowWidth() * 2, 732);
    for(short dirtCols = 0; dirtCols < 10; dirtCols++)
    {
        for(short dirtRows = 0; dirtRows < 20; dirtRows++)
        {
            Tile newTile = Tile(spawnPos, dirt1, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1200 + GameWindow::GetWindowWidth() * 2;
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(1510 + GameWindow::GetWindowWidth() * 2, 716);
    for(short i = 0; i < 31; i++)
    {
        Tile newTile = Tile(spawnPos, lightishStone, tileSize);

        tiles.emplace_back(newTile);

        spawnPos.x += i % 10 == 0? tileSize : 0;
        spawnPos.y -=tileSize;
    }

    spawnPos = Vector2(1400 + GameWindow::GetWindowWidth() * 2, 210);
    for(short cols = 0; cols < 2; cols++)
    {
        for(short rows = 0; rows < 12; rows++)
        {
            Tile newTile = Tile(spawnPos, platform, tileSize);
    
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
            Tile newTile = Tile(spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1880 + GameWindow::GetWindowWidth() * 2;
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(700 + GameWindow::GetWindowWidth() * 2, -64);
    for(short cols = 0; cols < 34; cols++)
    {
        for(short rows = 0; rows < 6; rows++)
        {
            Tile newTile = Tile(spawnPos, platform, tileSize);
    
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
            Tile newTile = Tile(spawnPos, platform, tileSize);
    
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
            Tile newTile = Tile(spawnPos, platform, tileSize);
    
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
            Tile newTile = Tile(spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 200 + GameWindow::GetWindowWidth() * 3;
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(980 + GameWindow::GetWindowWidth() * 3, 400);
    for(short rows = 0; rows < 6; rows++)
    {
        Tile newTile = Tile(spawnPos, platform, tileSize);

        tiles.emplace_back(newTile);

        spawnPos.x += tileSize;
    }

    spawnPos = Vector2(1800 + GameWindow::GetWindowWidth() * 3, 900);
    for(short cols = 0; cols < 2; cols++)
    {
        for(short rows = 0; rows < 16; rows++)
        {
            Tile newTile = Tile(spawnPos, platform, tileSize);
    
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
            Tile newTile = Tile(spawnPos, platform, tileSize);
    
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
            Tile newTile = Tile(spawnPos, platform, tileSize);
    
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
            Tile newTile = Tile(spawnPos, platform, tileSize);
    
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
            Tile newTile = Tile(spawnPos, platform, tileSize);
    
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
            Tile newTile = Tile(spawnPos, platform, tileSize);
    
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
            Tile newTile = Tile(spawnPos, platform, tileSize);
        
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
            Tile newTile = Tile(spawnPos, platform, tileSize);
    
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
            Tile newTile = Tile(spawnPos, platform, tileSize);
    
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
            Tile newTile = Tile(spawnPos, platform, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = 1600 + GameWindow::GetWindowWidth() * 5;
        spawnPos.y += tileSize;
    }

    start = spawnPos.x + tileSize * 4;
    spawnPos = {start, 800};
    for(short cols = 0; cols < 18; cols++)
    {
        for(short rows = 0; rows < 20; rows++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd == 1? end1 : end2, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }

    start += tileSize;
    spawnPos = {start, 0};
    while(spawnPos.y < GameWindow::GetWindowHeight())
    {
        Tile newTile = Tile(spawnPos,invisible, tileSize, true);
    
        tiles.emplace_back(newTile);
    
        spawnPos.y += tileSize;
    }
}



void TileManager::Level2Tiles()
{
    float start = 0;
    Vector2 spawnPos = Vector2(start, tileSize * 63);


    //\\//\\//\\//\\// 1st Slide //\\//\\//\\//\\// 
    for(short cols = 0; cols < 5; cols++)
    {
        for(short rows = 0; rows < 130; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    
    //\\//\\//\\//\\// 2nd Slide //\\//\\//\\//\\//
    
    start = tileSize * 10 + GameWindow::GetWindowWidth();
    spawnPos = {start, tileSize * 50};
    for(short cols = 0; cols < 20; cols++)
    {
        for(short rows = 0; rows < 20; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(GameWindow::GetWindowWidth() + 600, 550);
    for(short cols = 0; cols < 2; cols++)
    {
        for(short rows = 0; rows < 12; rows++)
        {
            Tile newTile = Tile(spawnPos, lightishStone, tileSize);
    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = GameWindow::GetWindowWidth() + 600;
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(GameWindow::GetWindowWidth() + 900, 400);
    for(short i = 0; i < 8; i++)
    {
        Tile newTile = Tile(spawnPos, lightishStone, tileSize);
    
        tiles.emplace_back(newTile);
    
        spawnPos.x += tileSize;
    }
    
    spawnPos = Vector2(GameWindow::GetWindowWidth() + 1500, 900);
    for(short i = 0; i < 8; i++)
    {
        Tile newTile = Tile(spawnPos, lightishStone, tileSize);
    
        tiles.emplace_back(newTile);
    
        spawnPos.x += tileSize;
    }
    
    spawnPos = Vector2(GameWindow::GetWindowWidth() + 1850, 800);
    for(short cols = 0; cols < 20; cols++)
    {
        for(short rows = 0; rows < 18; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        // Don't reset if it's the last iteration
        if(cols != 19) spawnPos.x = GameWindow::GetWindowWidth() + 1850;
        spawnPos.y += tileSize;
    }
    
    start = spawnPos.x;
    spawnPos.y = 500;
    for(short cols = 0; cols < 39; cols++)
    {
        for(short rows = 0; rows < 18; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        if(cols != 38) spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    
    //\\//\\//\\//\\// 3rd Slide //\\//\\//\\//\\//
    
    
    start = spawnPos.x;
    spawnPos = Vector2(GameWindow::GetWindowWidth() * 2, -tileSize * 10);
    for(short rows = 0; rows < 24; rows++)
    {
        Tile newTile = Tile(spawnPos, lightishStone, tileSize);    
        tiles.emplace_back(newTile);
    
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(GameWindow::GetWindowWidth() * 2, spawnPos.y);
    for(short cols = 0; cols < 2; cols++)
    {
        for(short rows = 0; rows < 13; rows++)
        {
            Tile newTile = Tile(spawnPos, lightishStone, tileSize);    
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = GameWindow::GetWindowWidth() * 2;
        spawnPos.y += tileSize;
    }
    
    spawnPos = {start - tileSize * 10, 200};
    for(short rows = 0; rows < 10; rows++)
    {
        Tile newTile = Tile(spawnPos, lightishStone, tileSize);    
        tiles.emplace_back(newTile);
    
        spawnPos.x += tileSize;
    }
    
    start = spawnPos.x;
    spawnPos.x = start;
    for(short cols = 0; cols < 60; cols++)
    {
        for(short rows = 0; rows < 10; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        if(cols != 59) spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    spawnPos.y = 200;
    start = spawnPos.x;
    for(short rows = 0; rows < 20; rows++)
    {
        Tile newTile = Tile(spawnPos, lightishStone, tileSize);
        tiles.emplace_back(newTile);
    
        spawnPos.x += tileSize;
    }
    
    spawnPos = {start, 600};
    for(short rows = 0; rows < 6; rows++)
    {
        Tile newTile = Tile(spawnPos, lightishStone, tileSize);
        tiles.emplace_back(newTile);
    
        spawnPos.x += tileSize;
    }
    
    spawnPos = Vector2(GameWindow::GetWindowWidth() * 2 + 1100, -400);
    for(short cols = 0; cols < 75; cols++)
    {
        for(short rows = 0; rows < 15; rows++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd == 0? darkStone2 : softDarkStone, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = GameWindow::GetWindowWidth() * 2 + 1100;
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(GameWindow::GetWindowWidth() * 2 + 1134, 1020);
    for(short cols = 0; cols < 4; cols++)
    {
        for(short rows = 0; rows < 24; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        if(cols != 3) spawnPos.x = GameWindow::GetWindowWidth() * 2 + 1134;
        spawnPos.y += tileSize;
    }
    
    spawnPos.y = 300;
    start = spawnPos.x;
    for(short cols = 0; cols < 50; cols++)
    {
        for(short rows = 0; rows < 20; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        if(cols != 49) spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    spawnPos = {start - tileSize, 700};
    for(short rows = 0; rows < 5; rows++)
    {
        Tile newTile = Tile(spawnPos, lightishStone, tileSize);
        tiles.emplace_back(newTile);
    
        spawnPos.x -= tileSize;
    }
    
    spawnPos = {start - tileSize * 11, 400};
    for(short rows = 0; rows < 5; rows++)
    {
        Tile newTile = Tile(spawnPos, lightishStone, tileSize);
        tiles.emplace_back(newTile);
    
        spawnPos.x += tileSize;
    }
    
    start = GameWindow::GetWindowWidth() * 2 + 1836;
    spawnPos = { start, 300 };
    for(short cols = 0; cols < 2; cols++)
    {
        for(short rows = 0; rows < 16; rows++)
        {
            Tile newTile = Tile(spawnPos, lightishStone, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    
    //\\//\\//\\//\\// 4th Slide //\\//\\//\\//\\//
    
    start = GameWindow::GetWindowWidth() * 3 + 300;
    spawnPos = { start, 600 };
    for(short cols = 0; cols < 2; cols++)
    {
        for(short rows = 0; rows < 12; rows++)
        {
            Tile newTile = Tile(spawnPos, lightishStone, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    start = GameWindow::GetWindowWidth() * 3 + 700;
    spawnPos = { start, 900 };
    for(short cols = 0; cols < 2; cols++)
    {
        for(short rows = 0; rows < 12; rows++)
        {
            Tile newTile = Tile(spawnPos, lightishStone, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    start = GameWindow::GetWindowWidth() * 3 + 950;
    spawnPos = { start, 500 };
    for(short cols = 0; cols < 2; cols++)
    {
        for(short rows = 0; rows < 14; rows++)
        {
            Tile newTile = Tile(spawnPos, lightishStone, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    start = GameWindow::GetWindowWidth() * 3 + 1500;
    spawnPos = { start, 500 };
    for(short cols = 0; cols < 2; cols++)
    {
        for(short rows = 0; rows < 14; rows++)
        {
            Tile newTile = Tile(spawnPos, lightishStone, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(GameWindow::GetWindowWidth() * 3 + 1800, 1000);
    for(short cols = 0; cols < 5; cols++)
    {
        for(short rows = 0; rows < 30; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        if(cols != 4) spawnPos.x = GameWindow::GetWindowWidth() * 3 + 1800;
        spawnPos.y += tileSize;
    }
    
    //\\//\\//\\//\\// 5th Slide //\\//\\//\\//\\//
    
    start = spawnPos.x;
    spawnPos = {start, 200};
    for(short cols = 0; cols < 56; cols++)
    {
        for(short rows = 0; rows < 16; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(GameWindow::GetWindowWidth() * 4 + 900, -300);
    for(short cols = 0; cols < 64; cols++)
    {
        for(short rows = 0; rows < 16; rows++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd == 0? darkStone2 : softDarkStone, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = GameWindow::GetWindowWidth() * 4 + 900;
        spawnPos.y += tileSize;
    }
    
    spawnPos = Vector2(GameWindow::GetWindowWidth() * 4 + 1000, 1000);
    for(short cols = 0; cols < 5; cols++)
    {
        for(short rows = 0; rows < 30; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = GameWindow::GetWindowWidth() * 4 + 1000;
        spawnPos.y += tileSize;
    }
    
    //\\//\\//\\//\\// 5th/6th Slide //\\//\\//\\//\\//
    
    spawnPos = Vector2(GameWindow::GetWindowWidth() * 4 + 1600, 450);
    for(short cols = 0; cols < 50; cols++)
    {
        for(short rows = 0; rows < 25; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = GameWindow::GetWindowWidth() * 4 + 1600;
        spawnPos.y += tileSize;
    }


    //\\//\\//\\//\\// 6th/7th Slide //\\//\\//\\//\\//
    
    spawnPos = Vector2(GameWindow::GetWindowWidth() * 5 + 1800, 450);
    for(short cols = 0; cols < 50; cols++)
    {
        for(short rows = 0; rows < 20; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = GameWindow::GetWindowWidth() * 5 + 1800;
        spawnPos.y += tileSize;
    }


    //\\//\\//\\//\\// 7th Slide //\\//\\//\\//\\//

    spawnPos = Vector2(GameWindow::GetWindowWidth() * 6 + 200, 600);
    for(short cols = 0; cols < 30; cols++)
    {
        for(short rows = 0; rows < 16; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        if(cols != 29) spawnPos.x = GameWindow::GetWindowWidth() * 6 + 200;
        spawnPos.y += tileSize;
    }

    start = spawnPos.x;
    spawnPos = {start, 900};
    for(short cols = 0; cols < 15; cols++)
    {
        for(short rows = 0; rows < 16; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }

    spawnPos = Vector2(GameWindow::GetWindowWidth() * 6 + 1200, 900);
    for(short cols = 0; cols < 15; cols++)
    {
        for(short rows = 0; rows < 16; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        if(cols != 14) spawnPos.x = GameWindow::GetWindowWidth() * 6 + 1200;
        spawnPos.y += tileSize;
    }

    start = spawnPos.x;
    spawnPos = Vector2(start, 600);
    for(short cols = 0; cols < 30; cols++)
    {
        for(short rows = 0; rows < 16; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        if(cols != 29) spawnPos.x = start;
        spawnPos.y += tileSize;
    }

    start = spawnPos.x;
    spawnPos = Vector2(start, 450);
    for(short cols = 0; cols < 45; cols++)
    {
        for(short rows = 0; rows < 24; rows++)
        {
            const short rnd1 = rand() % 2;
            const short rnd2 = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd1 == 0? hardDarkStone: rnd2 == 0? darkStone3 : darkStone2, tileSize);
            tiles.emplace_back(newTile);
    
            spawnPos.x += tileSize;
        }
        spawnPos.x = start;
        spawnPos.y += tileSize;
    }

    
    //\\//\\//\\//\\// 8th Slide //\\//\\//\\//\\//

    spawnPos = Vector2(GameWindow::GetWindowWidth() * 8 - 300, GameWindow::GetWindowHeight());
    for(short cols = 0; cols < 8; cols++)
    {
        for(short rows = 0; rows < 8; rows++)
        {
            const short rnd = rand() % 2;
            Tile newTile = Tile(spawnPos, rnd == 0? end2: end1, tileSize, true);
            tiles.emplace_back(newTile);
    
            spawnPos.x -= tileSize;
        }
        spawnPos.x = GameWindow::GetWindowWidth() * 8 - 300;
        spawnPos.y -= tileSize;
    }
}
