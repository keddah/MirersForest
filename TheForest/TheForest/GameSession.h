#pragma once
#include "Level.h"

class GameSession
{
public:
    GameSession();
    ~GameSession() = default;

    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);
    void Draw();
    
private:
    Level level1 {0};
};
