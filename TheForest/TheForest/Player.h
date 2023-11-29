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

    void Init();
    
    const SpriteRenderer& GetRenderer() const { return renderer; } 
    
    PlayerController& Controller() { return controller; }
    
private:
    void UpdateRectangle();

    void Collisions();
    void Move();
    void Jump();
    void Crouch();
    void UnCrouch();
        
    const std::string spritePath = "Sprites/testspritesheet.png";
    bool initialised = false;
    
    SDL_Rect rect;
    SpriteRenderer renderer = SpriteRenderer(spritePath, pos, true);
    
    PlayerController controller;


    // Movement
    const int maxSpeed = 100;
    bool canMove = true;
    Vector2 pos = Vector2();
    short direction = 0;
    short moveSpeed = 5;
    short jumpForce = 250;

    std::vector<Tile>& floor;

    Vector2 groundLevel;
};
