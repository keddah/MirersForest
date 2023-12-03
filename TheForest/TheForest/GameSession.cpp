#include "GameSession.h"

#include "GameSingletons.h"

GameSession::GameSession()
{
    spriteRenderers.push_back(player.GetRenderer());

    tileManager.MakeTiles();
    for (auto& tile : tileManager.GetTiles())
    {
        staticRenderers.push_back(tile.GetRenderer());
    }
}

void GameSession::Update(float deltaTime)
{
    player.Update(deltaTime);
}

void GameSession::FixedUpdate(float deltaTime)
{
    player.FixedUpdate(deltaTime);
}

void GameSession::Draw()
{
    for (auto& renderer : staticRenderers) renderer.Draw(false);
    for (auto& renderer : spriteRenderers) renderer.Draw(false);
    player.DrawBullets();
}
