#include "Level.h"

Level::Level(short lvlNum) : currentLevel(lvlNum)
{
    bkg.ChangeSpriteSheet(currentLevel);
    tileManager.MakeTiles(currentLevel);
    slimeManger.SpawnSlimes(currentLevel);
    flowerManager.SpawnFlowers(currentLevel);
    
    audio.PlayMusic();
}

Level::~Level()
{
    delete &ui;
    delete &tileManager;
    delete &slimeManger;
    delete &flowerManager;
    delete &player;
}

void Level::Update(float deltaTime)
{
    player.Update(deltaTime);
    slimeManger.Update(deltaTime);
    flowerManager.Update(deltaTime);
    ui.Update(deltaTime);

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
    
    else SyncSlides();
}

void Level::FixedUpdate(float deltaTime)
{
    player.FixedUpdate(deltaTime);
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

    bkg.ChangeSpriteSheet(currentLevel);
    
    player.Reset();
    completed = false;
    tileManager.MakeTiles(currentLevel, true);
    slimeManger.Reset(currentLevel);
    flowerManager.SpawnFlowers(currentLevel, true);
}
