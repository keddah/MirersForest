#include "Level.h"

#include "GameSingletons.h"

Level::Level(short lvlNum)
{
    tileManager.MakeTiles(0);
}

void Level::Update(float deltaTime)
{
    player.Update(deltaTime);
    slimeManger.Update(deltaTime);
    flowerManager.Update(deltaTime);
    
    SyncSlides();
    // print("level: " << currentSlide)      
}

void Level::FixedUpdate(float deltaTime)
{
    player.FixedUpdate(deltaTime);
}

void Level::DrawSlide()
{
    bkg.Draw();
    flowerManager.Draw();
    tileManager.Draw();
    slimeManger.Draw();
    player.Draw();
}

void Level::SyncSlides()
{
    tileManager.SetLevelSlide(currentSlide);
    slimeManger.SetLevelSlide(currentSlide);
    flowerManager.SetLevelSlide(currentSlide);
}
