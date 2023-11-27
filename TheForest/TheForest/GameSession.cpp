#include "GameSession.h"

#include "GameSingletons.h"

GameSession::GameSession()
{
    player.Init();
    renderers.push_back(player.GetRenderer());
    renderers.push_back(tileManager.GetTiles()[0].GetRenderer());
}

void GameSession::Update(float deltaTime)
{
    player.Update(deltaTime);
}

void GameSession::Draw()
{
    for (auto& renderer : renderers)
    {
        renderer.Draw();
    }
}
