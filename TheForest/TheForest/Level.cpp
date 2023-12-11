#include "Level.h"

Level::Level(short lvlNum)
{
    manuals.emplace_back(bkg);
    
    tileManager.MakeTiles(0);
    for (auto& tile : tileManager.GetTiles())
    {
        manuals.emplace_back(tile.GetRenderer());
    }
    
    sprites.emplace_back(player.GetRenderer());
}

void Level::Update(float deltaTime)
{
    player.Update(deltaTime);
    slimeManger.Update(deltaTime);
}

void Level::FixedUpdate(float deltaTime)
{
    player.FixedUpdate(deltaTime);
}

void Level::Draw()
{
    for (auto& renderer : manuals) renderer.Draw(false);

    slimeManger.Draw();
    
    // Draw weapons before drawing the rest of the sprite renderers (THE PLAYER) so that the arrow is behind the player
    player.DrawWeapons();
    for (auto& renderer : sprites) renderer.Draw(false);
}
