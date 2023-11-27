#pragma once

#include <vector>

#include "Controllers.h"
#include "Physics.h"
#include "SpriteRenderer.h"

class Player : public Physics
{
public:
    Player() = default;
    ~Player() = default;
    void Update(float deltaTime);

    void Init();
    
    const SpriteRenderer& GetRenderer() const { return renderer; } 
    
    PlayerController& Controller() { return controller; }
    
private:
    void UpdateRectangle();

    void Move();
    void Jump();
    void Crouch();
    void UnCrouch();
        
    const std::string spritePath = "Sprites/testspritesheet.png";
    bool initialised = false;
    
    SpriteRenderer renderer = SpriteRenderer(spritePath, pos, true);
    
    PlayerController controller;


    // Movement
    SDL_Rect rect;
    Vector2 pos = Vector2();
    short direction = 0;
    short moveSpeed = 5;
    short jumpForce = 20;
};
