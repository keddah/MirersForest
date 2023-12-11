#include "Level.h"

#include "GameSingletons.h"

Level::Level(short lvlNum)
{
    // Create slides
    for(int i = 0; i < 15; i++) slides.emplace_back(this);

    tileManager.MakeTiles(0);
}

void Level::UpdateSlide(float deltaTime)
{
    player.Update(deltaTime);
    slimeManger.Update(deltaTime);
}

void Level::FixedUpdate(float deltaTime)
{
    player.FixedUpdate(deltaTime);
}

void Level::DrawSlide()
{
    bkg.Draw(0);

    tileManager.Draw();
    
    slimeManger.Draw();

    player.Draw();
}


////////// Slide class
void Level::Slide::Draw()
{
    for (auto& renderer : manuals) renderer.Draw(level.currentSlide, false);
    for (auto& renderer : sprites) renderer.Draw(level.currentSlide, false);
}
