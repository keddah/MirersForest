#pragma once
#include "Level.h"

class GameSession
{
public:
    GameSession() = default;
    ~GameSession() { delete &level; }

    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);
    void Draw();
    
private:
    Level level {0};
};
