#include "GameSession.h"

#include "GameSingletons.h"

GameSession::GameSession()
{
}

void GameSession::Update(float deltaTime)
{
    level1.Update(deltaTime);
}

void GameSession::FixedUpdate(float deltaTime)
{
    level1.FixedUpdate(deltaTime);
}

void GameSession::Draw()
{
    level1.DrawSlide();
}
