#include "GameSession.h"

#include "GameSingletons.h"

GameSession::GameSession()
{
    int screenWidth, screenHeight;
    SDL_GetWindowSize(GameWindow::GetWindow(), &screenWidth, &screenHeight);
}

void GameSession::Update(float deltaTime)
{
    level1.UpdateSlide(deltaTime);
}

void GameSession::FixedUpdate(float deltaTime)
{
    level1.FixedUpdate(deltaTime);
}

void GameSession::Draw()
{
    level1.DrawSlide();
}
