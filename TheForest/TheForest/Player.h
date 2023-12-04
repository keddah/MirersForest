#pragma once

#include "Physics.h"
#include "SpriteRenderer.h"
#include "Tile.h"
#include "WeaponController.h"

class Player : public Physics
{
public:
    Player(std::vector<Tile>& floorRef);
    ~Player() = default;

    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);
    void DrawBullets() { wc.DrawBullets(); } 
    
    const SpriteRenderer& GetRenderer() const { return renderer; } 
    
    PlayerController& Controller() { return controller; }
    
private:
    const std::string spritePath = "Sprites/testspritesheet.png";
    SpriteRenderer renderer = SpriteRenderer(spritePath, position, true);
    void UpdateRectangle();

    void Collisions();
    void Move(float deltaTime);
    void Deceleration(float deltaTime);
    void Jump();

    SDL_FRect rect;
    
    PlayerController controller;


    //////////// Weapons
    WeaponController wc = WeaponController(controller, rect);
    
    
    //////////// Movement
    bool canMove = true;
    short direction = 0;
    
    ////// Acceleration/Deceleration
    const float accelerationRate = 120;
    float moveSpeed = 5;
    
    bool decelerating;
    
    ////// Jumping
    bool jumping;
    bool jumpBuffer;
    const float airControl = 5.5f;
    const float jumpHeight = 5;
    const float jumpForce = 25;
    
    std::vector<Tile>& floor;
};
