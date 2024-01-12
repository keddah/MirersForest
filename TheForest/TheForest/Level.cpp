/**************************************************************************************************************
* Level - Code
*
* The code file for the Level class. Responsible for calling all of the update and draw functions for everything that requires them in the level.
* Also responsible for creating the correct level tiles, slime and flower formation. 
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#include "Level.h"

Level::Level(const short lvlNum) : currentLevel(lvlNum)
{
    bkg.ChangeSpriteSheet(currentLevel);
    tileManager.MakeTiles(currentLevel);
    slimeManger.SpawnSlimes(currentLevel);
    flowerManager.SpawnFlowers(currentLevel);
    
    audio.PlayMusic();
}


void Level::FixedUpdate(float deltaTime)
{
    player.FixedUpdate(deltaTime);
    slimeManger.FixedUpdate(deltaTime);
    flowerManager.FixedUpdate(deltaTime);
}

void Level::Update(float deltaTime)
{
    player.Update(deltaTime);
    ui.Update(deltaTime);
    slimeManger.Update(deltaTime);
    
    // Check if it should go to the next level after setting completed
    completed = player.IsFinished();
    NextLevel();

    if(player.IsRespawning())
    {
        tileManager.Reset();

        // Need to reset the player first so that the level slide gets updated
        player.Reset();
        slimeManger.Reset(currentLevel);
        flowerManager.Reset();
    }

    // Don't sync the slides if the player is respawning (since the slides all need to be set to 0 anyway)
    else SyncSlides();
}

void Level::Draw()
{
    // The background is behind everything
    bkg.Draw();
    tileManager.Draw();
    
    // Flowers renderer above tiles so placement is easier to see 
    flowerManager.Draw();
    slimeManger.Draw();
    player.Draw();

    // Draw the UI on top of everything
    ui.Draw();
}

void Level::SyncSlides()
{
    tileManager.SetLevelSlide(currentSlide);
    slimeManger.SetLevelSlide(currentSlide);
    flowerManager.SetLevelSlide(currentSlide);
}

void Level::NextLevel()
{
    if(!completed) return;

    if(currentLevel != levelCount) currentLevel++;
    if(currentLevel == levelCount)
    {
        ui.EndGame();
        return;
    }

    // Change the level background
    bkg.ChangeSpriteSheet(currentLevel);

    // Reset everything
    player.Reset();
    completed = false;
    tileManager.MakeTiles(currentLevel, true);
    slimeManger.Reset(currentLevel);
    flowerManager.SpawnFlowers(currentLevel, true);
}
