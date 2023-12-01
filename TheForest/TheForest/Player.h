#pragma once

#include <vector>

#include "Controllers.h"
#include "Physics.h"
#include "SpriteRenderer.h"
#include "Tile.h"

class Player : public Physics
{
public:
    Player(std::vector<Tile>& floorRef);
    ~Player() = default;
    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);

    void Init();
    
    const SpriteRenderer& GetRenderer() const { return renderer; } 
    
    PlayerController& Controller() { return controller; }
    
private:
    void UpdateRectangle();

    void Collisions();
    void Move(float deltaTime);
    void Deceleration(bool turning, float deltaTime);
    void Jump();
    void Crouch();
    void UnCrouch();
        
    const std::string spritePath = "Sprites/testspritesheet.png";
    bool initialised = false;
    
    SDL_Rect rect;
    SpriteRenderer renderer = SpriteRenderer(spritePath, pos, true);
    
    PlayerController controller;


    //////////// Movement
    bool canMove = true;
    short direction = 0;
    
    ////// Acceleration/Deceleration
    const float accelerationRate = 120;
    float moveSpeed = 5;
    
    // How fast the character should decelerate
    float slowSpeed = 10;
    const float decelerationRate = 175;
    bool decelerating;
    
    ////// Jumping
    bool jumping;
    bool jumpBuffer;
    const float airControl = 7.5f;
    const float jumpHeight = 5;
    const float jumpForce = 25;
    
    std::vector<Tile>& floor;
};
