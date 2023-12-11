#pragma once

#include "Physics.h"
#include "Renderers.h"
#include "Controllers.h"
#include "Projectile.h"
#include "TileManager.h"


class Player : public Physics
{
public:
    Player(TileManager& tm);
    ~Player() = default;

    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);

    void DrawWeapons() { wc.Draw(); }

    void Float();
    void TakeDamage();
    
    std::vector<Projectile>& GetActiveBullets() { return wc.GetActiveBullets(); }
    const SpriteRenderer& GetRenderer() const { return *renderer; } 
    const SDL_FRect& GetRect() const { return rect; } 
    PlayerController& Controller() { return controller; }

private:
    class WeaponController
    {
    public:
        WeaponController(Player* plyr);
        ~WeaponController() = default;

        void Update(float deltaTime);
        void UpdateBullets(float deltaTime);
        void Draw();
        std::vector<Projectile>& GetActiveBullets() { return activeBullets; }

    private:
        Player& thisPlayer;
        
        void WeaponSelection();
        void ConfigureWeapon();
        void Shooting(float deltaTime);

        //Variants
        void Shotgun();
        
        float GetShootAngle() const;

        void NextWeapon();
        void PreviousWeapon();
        
        bool canShoot = true;
        float shootTimer;
    
        Projectile::EWeaponTypes selectedWeapon = Projectile::EWeaponTypes::Seed;

        std::vector<Projectile> activeBullets = std::vector<Projectile>();

        Vector2 arrowPos;
        float arrowOffset = 86.5f;
        SpriteRenderer arrow = SpriteRenderer(
{
            "Sprites/Arrows/seed_arrow.png",
            "Sprites/Arrows/petal_arrow.png",
            "Sprites/Arrows/sun_arrow.png",
            "Sprites/Arrows/thorn_arrow.png"
            },  arrowPos, false);
        
        const int seedForce = 15;
        const int petalForce = 13;
        const int sunForce = 20;
        // const int thornForce = 8;

        const float seedDelay = .8f;
        const float petalDelay = .125f;
        const float sunDelay = 2;
        // const float thornDelay = 1.2f;

        // Gravity Multipliers
        const float seedGravity = .03f;
        const float petalGravity = .05f;
        const float sunGravity = 0;
        // const float thornGravity = .01f ;

        const float seedRepulsion = 2.5f;
        const float petalRepulsion = .875f;
        const float sunRepulsion = 20;
        // const float thornRepulsion = 0 ;

        // Special uses 2
        const short seedAmmo = 3;

        // Special uses 10
        const short petalAmmo = 30;

        // Special uses 2
        const short sunAmmo = 6;

        // Always uses 1
        // const short thornAmmo = 5;
    
	
        // Projectile spawn position
        Vector2 spawnPos;
        const Vector2 spawnOffset = {-90, 75};

        // The weapon type .. The force .. The size .. The Delay .. The ammo count .. The gravity multiplier .. The repulsion force
        // When Getting :
        // Type = 0 .. Force = 1 .. .. Delay = 2 .. Ammo = 3 .. Gravity = 4 .. Repulsion = 5
        std::tuple<Projectile::EWeaponTypes, float, float, short, float, float> weapon;
    };

    class Camera
    {
    public:
        Camera(Player* plyr);
        void Update();

    private:
        void FollowPlayer();
    
        Player& thisPlayer;

        int screenWidth, screenHeight;
        short slide;
    };
    
    TileManager& tileManager;
    
    const std::vector<std::string> spritePaths = {"Sprites/idleTileSheet.png", "Sprites/runTileSheet.png", "Sprites/idleTileSheet_dmg.png", "Sprites/runTileSheet_dmg.png"};
    SpriteRenderer* renderer = new SpriteRenderer(spritePaths, position);

    short idleAnimation = 0;
    short runAnimation = 1;
    short fallAnimation = 2;
    
    
    Vector2 GetVelocity() const { return velocity; }
    Vector2 GetPosition() const { return position; }

    void Propel(Vector2 dir, float force);
    
    void Collisions();
    void Move(float deltaTime);
    void Deceleration(float deltaTime);
    void Jump();
    void UpdateRectangle();

    void Death();
    void DamageTimer(float deltaTime);
    
    SDL_FRect rect;
    
    PlayerController controller;

    Camera cam = Camera (this);

    //////////// Weapons
    WeaponController wc = WeaponController(this);
    
    
    //////////// Movement
    bool canMove = true;
    short direction = 0;

    bool setFloatTimer;
    const float floatDuration = .5f;
    float floatTimer;
    
    
    ////// Acceleration/Deceleration
    const float accelerationRate = 100;
    float moveSpeed = .9f;
    const float maxMoveSpeed = 10;
    
    bool decelerating;
    
    ////// Jumping
    bool jumping;
    bool jumpBuffer;
    const float airControl = 5.5f;
    const float jumpHeight = 5;
    const float jumpForce = 25;


    ////// Health/Damage
    const short maxHealth = 3;
    short health = maxHealth;

    bool isDamaged;
    const float dmgCooldown = 1.5f;
    float dmgTimer;
};
