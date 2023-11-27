#pragma once
#include "Player.h"

class GameSession
{
public:
    GameSession();
    ~GameSession() = default;

    void Update(float deltaTime);
    void Draw();
    
private:
    std::vector<SpriteRenderer> renderers = std::vector<SpriteRenderer>();
    
    Player player;
};
