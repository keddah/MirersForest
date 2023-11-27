#pragma once

#include <vector>

#include "Controllers.h"
#include "SpriteRenderer.h"

class Player
{
public:
    Player();
    ~Player() = default;
    void Update(float deltaTime);

    void Init();
    
    const SpriteRenderer& GetRenderer() const { return *renderer; } 
    
    PlayerController& Controller() { return controller; }
    
private:
    void UpdateRectangle();
    
    const std::string spritePath = "Sprites/testspritesheet.png";
    bool initialised = false;
    
    SpriteRenderer* renderer;
    
    PlayerController controller;

    SDL_Rect rect;
    Vector2 pos = Vector2();
    
};
