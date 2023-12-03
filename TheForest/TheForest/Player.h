#pragma once

#include <vector>

#include "Controllers.h"
#include "Physics.h"
#include "Projectile.h"
#include "SpriteRenderer.h"
#include "Tile.h"

class Player : public Physics
{
public:
    Player(std::vector<Tile>& floorRef);
    ~Player() = default;
    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);

    void UpdateBullets();
    void DrawBullets();
    
    const SpriteRenderer& GetRenderer() const { return renderer; } 
    
    PlayerController& Controller() { return controller; }
    
private:
    const std::string spritePath = "Sprites/testspritesheet.png";
    SpriteRenderer renderer = SpriteRenderer(spritePath, _position, true);
    void UpdateRectangle();

    void Collisions();
    void Move(float deltaTime);
    void Deceleration(bool turning, float deltaTime);
    void Jump();

    void Shooting();
    
    SDL_Rect rect;
    
    PlayerController controller;


    //////////// Weapons
    const int projSpawnOffset = 40;
    Vector2 projectileSpawn;

    bool canShoot = true;
    float shootTimer;
    Projectile::EWeaponTypes selectedWeapon = Projectile::EWeaponTypes::Seed;

    std::vector<Projectile> activeBullets = std::vector<Projectile>();
    
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
    const float airControl = 7.5f;
    const float jumpHeight = 5;
    const float jumpForce = 25;
    
    std::vector<Tile>& floor;
};
