#pragma once
#include "Level.h"

class GameSession
{
public:
    GameSession() = default;
    ~GameSession() { delete &level; }

    void Update(float deltaTime) { level.Update(deltaTime); }
    void FixedUpdate(float deltaTime) { level.FixedUpdate(deltaTime); }
    void Draw() { level.Draw(); }
    
private:
    Level level {0};
};
