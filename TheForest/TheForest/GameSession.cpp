#include "GameSession.h"

#include "GameSingletons.h"

GameSession::GameSession()
{
    player.Init();
    renderers.push_back(player.GetRenderer());
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
