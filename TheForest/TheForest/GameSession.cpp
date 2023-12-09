#include "GameSession.h"

#include "GameSingletons.h"

GameSession::GameSession()
{
    int screenWidth, screenHeight;
    SDL_GetWindowSize(GameWindow::GetWindow(), &screenWidth, &screenHeight);
    
    manualRenderers.emplace_back(bkg);
    
    tileManager.MakeTiles();
    for (auto& tile : tileManager.GetTiles())
    {
        manualRenderers.emplace_back(tile.GetRenderer());
    }
    
    spriteRenderers.emplace_back(player.GetRenderer());
}

void GameSession::Update(float deltaTime)
{
    player.Update(deltaTime);
    slimeManger.Update(deltaTime);
}

void GameSession::FixedUpdate(float deltaTime)
{
    player.FixedUpdate(deltaTime);
}

void GameSession::Draw()
{
    for (auto& renderer : manualRenderers) renderer.Draw(false);

    slimeManger.Draw();
    
    // Draw weapons before drawing the rest of the sprite renderers (THE PLAYER) so that the arrow is behind the player
    player.DrawWeapons();
    for (auto& renderer : spriteRenderers) renderer.Draw(false);
}
