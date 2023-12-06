#pragma once

#include "Physics.h"
#include "SpriteRenderer.h"
#include "Tile.h"
#include "Controllers.h"
#include "Projectile.h"


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
    class WeaponController
    {
    public:
        WeaponController(Player* plyr);
        ~WeaponController() = default;

        void Update(float deltaTime);
        void DrawBullets();

    private:
        Player& thisPlayer;

        void WeaponSelection();
        void Shooting();
        float GetShootAngle() const;
        
        bool canShoot = true;
        float shootTimer;
    
        Projectile::EWeaponTypes selectedWeapon = Projectile::EWeaponTypes::Seed;

        std::vector<Projectile> activeBullets = std::vector<Projectile>();

        const int seedForce = 30;
        const int petalForce = 30;
        const int sunForce = 8;
        const int thornForce = 8;

        const float seedDelay = .8f;
        const float petalDelay = .125f;
        const float sunDelay = 2;
        const float thornDelay = 1.2f;

        // Gravity Multipliers
        const float seedGravity = .3f;
        const float petalGravity = .5f;
        const float sunGravity = 0;
        const float thornGravity = .1f ;

        const float seedRepulsion = 75;
        const float petalRepulsion = 20;
        const float sunRepulsion = 200;
        const float thornRepulsion = 0 ;

	
        const Vector2 seedSize {12,12};
        const Vector2 petalSize {6,6};
        const Vector2 sunSize {400,24};
        const Vector2 thornSize {250,10};

    
        // Special uses 2
        const short seedAmmo = 3;

        // Special uses 10
        const short petalAmmo = 30;

        // Special uses 2
        const short sunAmmo = 6;

        // Always uses 1
        const short thornAmmo = 5;
    
	
        // Projectile spawn position
        Vector2 spawnPos;
        const int projSpawnOffset = 40;
        short direction;

        // The weapon type .. The force .. The size .. The Delay .. The ammo count .. The gravity multiplier .. The repulsion force
        // When Getting :
        // Type = 0 .. Force = 1 .. Size = 2 .. Delay = 3 .. Ammo = 4 .. Gravity = 5 .. Repulsion = 6
        std::tuple<Projectile::EWeaponTypes, float, Vector2, float, short, float, float> weapon;
    };
    
    const std::vector<std::string> spritePaths = {"Sprites/idleTileSheet.png", "Sprites/runTileSheet.png"};
    SpriteRenderer renderer = SpriteRenderer(spritePaths, position);

    short idleAnimation = 0;
    short runAnimation = 1;
    short fallAnimation = 2;
    
    
    void UpdateRectangle();
    Vector2 GetVelocity() const { return velocity; }
    Vector2 GetPosition() const { return position; }
    void Collisions();

    void Propel(Vector2 dir, float force);
    
    void Move(float deltaTime);
    void Deceleration(float deltaTime);
    void Jump();

    SDL_FRect rect;
    
    PlayerController controller;


    //////////// Weapons
    WeaponController wc =  WeaponController(this);
    
    
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
