#include "GameSession.h"

#include "GameSingletons.h"

void GameSession::Update(float deltaTime)
{
    level.Update(deltaTime);
}

void GameSession::FixedUpdate(float deltaTime)
{
    level.FixedUpdate(deltaTime);
}

void GameSession::Draw()
{
    level.Draw();
}
