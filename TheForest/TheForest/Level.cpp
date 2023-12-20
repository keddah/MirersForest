#include "Level.h"

Level::Level(short lvlNum) : currentLevel(lvlNum)
{
    tileManager.MakeTiles(currentLevel);
    slimeManger.SpawnSlimes(currentLevel);
    
    audio.PlayMusic();
}

void Level::Update(float deltaTime)
{
    player.Update(deltaTime);
    slimeManger.Update(deltaTime);
    flowerManager.Update(deltaTime);
    ui.Update(deltaTime);
    

    if(player.IsRespawning())
    {
        tileManager.Reset();
        slimeManger.Reset();
        player.Reset();
        flowerManager.Reset();
    }
    
    SyncSlides();
}

void Level::FixedUpdate(float deltaTime)
{
    player.FixedUpdate(deltaTime);
}

void Level::DrawSlide()
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
