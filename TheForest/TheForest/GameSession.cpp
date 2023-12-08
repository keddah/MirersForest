#include "GameSession.h"

#include "GameSingletons.h"

GameSession::GameSession()
{
    int screenWidth, screenHeight;
    SDL_GetWindowSize(GameWindow::GetWindow(), &screenWidth, &screenHeight);
    
    manualRenderers.push_back(bkg);
    
    tileManager.MakeTiles();
    for (auto& tile : tileManager.GetTiles())
    {
        manualRenderers.push_back(tile.GetRenderer());
    }
    
    spriteRenderers.push_back(player.GetRenderer());
    spriteRenderers.push_back(test.GetRenderer());
}

void GameSession::Update(float deltaTime)
{
    player.Update(deltaTime);
    test.Update(deltaTime);
}

void GameSession::FixedUpdate(float deltaTime)
{
    player.FixedUpdate(deltaTime);
}

void GameSession::Draw()
{
    for (auto& renderer : manualRenderers) renderer.Draw(false);

    // Draw weapons before drawing the rest of the sprite renderers (THE PLAYER) so that the arrow is behind the player
    player.DrawWeapons();
    for (auto& renderer : spriteRenderers) renderer.Draw(false);
}
