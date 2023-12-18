#include "Level.h"

Level::Level(short lvlNum)
{
    tileManager.MakeTiles(0);

    audio.PlayMusic();

    ui.TimerOnOff(true);
}

void Level::Update(float deltaTime)
{
    player.Update(deltaTime);
    slimeManger.Update(deltaTime);
    flowerManager.Update(deltaTime);
    ui.Update(deltaTime);
    
    SyncSlides();
    // print("level: " << currentSlide)      
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
