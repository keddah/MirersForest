/**************************************************************************************************************
* Game Session - Header
*
* The header file for the Game session class. Creates a Level object and runs the looping functions (Update/Draw) 
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

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
    Level level;
};
