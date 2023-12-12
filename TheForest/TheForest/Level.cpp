#include "Level.h"

#include "GameSingletons.h"

Level::Level(short lvlNum)
{
    // Create slides
    // for(int i = 0; i < 15; i++) slides.emplace_back(this);

    tileManager.MakeTiles(0);
}

void Level::Update(float deltaTime)
{
    player.Update(deltaTime);
    slimeManger.Update(deltaTime);
    
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
    tileManager.Draw();
    slimeManger.Draw();
    player.Draw();
}

void Level::SyncSlides()
{
    tileManager.SetLevelSlide(currentSlide);
    slimeManger.SetLevelSlide(currentSlide);
}
