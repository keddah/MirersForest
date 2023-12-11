#include "Level.h"

#include "GameSingletons.h"

Level::Level(short lvlNum)
{
    // Create slides
    for(int i = 0; i < 15; i++) slides.emplace_back(this);

    tileManager.MakeTiles(0);

    // Adding the tile to the correct slide
    for (auto& tile : tileManager.GetTiles())
    {
        int screen;
        SDL_GetWindowSize(GameWindow::GetWindow(), &screen, NULL);
        
        tile.SetSlide(static_cast<short>(round(tile.GetPosition().x / screen)));
        slides[tile.GetLevelSlide()].AddManualRenderer(tile.GetRenderer());
    }
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
    
    slides[currentSlide].Draw();
    slimeManger.Draw();


    // Draw weapons before drawing the rest of the sprite renderers (THE PLAYER) so that the arrow is behind the player
    player.DrawWeapons();
    player.Draw();
}


////////// Slide class
void Level::Slide::Draw()
{
    for (auto& renderer : manuals) renderer.Draw(level.currentSlide, false);
    for (auto& renderer : sprites) renderer.Draw(level.currentSlide, false);
}
