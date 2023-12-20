#pragma once

#include "AudioManager.h"
#include "Physics.h"
#include "Renderers.h"
#include "Controllers.h"
#include "Projectile.h"
#include "TileManager.h"


class Player : public Physics
{
public:
    Player(const std::vector<Tile>& floorTiles, short& slide, const AudioManager& sound);
    ~Player() = default;

    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);

    // Draw weapons before drawing the player so that the arrow is behind the player.
    void Draw() { wc.Draw(); renderer.Draw(); }

    short GetLevelSlide() const { return currentSlide; }

    bool Respawn(const bool force = false)
    {
        if(force) respawning = true;
        else respawning = controller.JumpBtnDown() && dead;
        return respawning;
    }
    bool IsRespawning() const { return respawning; }
    void Reset();
    void Unpause();
    
    bool GivePowerup();
    void TakeDamage();
    void Float();

////////////// Gets
    std::vector<Projectile>& GetActiveBullets() { return wc.GetActiveBullets(); }
    const SpriteRenderer& GetRenderer() const { return renderer; } 
    const SDL_FRect& GetRect() const { return rect; } 

    bool IsPaused() const { return paused; }
    
    bool IsDead() const { return dead; }
    void Kill() { dead = true; }
    
    ///// UI related
    float GetAmmo() const { return wc.GetAmmo(); }
    float GetMaxAmmo() const { return wc.GetMaxAmmo(); }
    short GetHealth() const { return health; }

    Vector2 GetMousePos() const { return controller.GetMousePosition(); }
    bool LMB() const { return controller.IsLMB(); }
    
    Projectile::EWeaponTypes GetType() const { return wc.GetType(); }
    
    float GetWeaponCooldown() const { return wc.GetCooldown(); }
    float GetShootTimer() const { return wc.GetShootTimer(); }
    
private:
    class WeaponController
    {
    public:
        WeaponController(Player* pP);
        ~WeaponController() = default;

        void Update(float deltaTime);
        void Draw();
        std::vector<Projectile>& GetActiveBullets() { return activeBullets; }

        Projectile::EWeaponTypes GetType() const { return std::get<0>(weapon); }
        
        float GetCooldown() const { return std::get<2>(weapon); }
        float GetShootTimer() const { return ammo == 0? 0 : shootTimer; }
        
        short GetAmmo() const { return ammo; }
        short GetMaxAmmo() const { return maxAmmo; }

        bool AmmoFull() const { return ammo == maxAmmo;  }
        void Refill() { ammo = maxAmmo;  }

    private:
        // player reference
        Player& rP;
        // The weapon type .. The force .. The size .. The Delay .. The ammo count .. The gravity multiplier .. The repulsion force
        // When Getting :
        // Type = 0 .. Force = 1 .. .. Delay = 2 .. AmmoCost = 3 .. Gravity = 4 .. Repulsion = 5
        std::tuple<Projectile::EWeaponTypes, float, float, short, float, float> weapon;

        void UpdateBullets(float deltaTime);

        void WeaponSelection();
        void ConfigureWeapon();
        void Shooting(float deltaTime);
        float GetShootAngle() const;

        //Variants
        void Shotgun();

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
        const int petalForce = 12;
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

        ///// Ammo
        const short maxAmmo = 45;
        short ammo = maxAmmo;
        
        const short seedCost = 8;
        const short petalCost = 1;
        const short sunCost = 15;
        // const short thornCost = 10;
    
	
        // Projectile spawn position
        Vector2 spawnPos;
        const Vector2 spawnOffset = {-90, 75};
    };
    
    const std::vector<Tile>& tiles;
    short& currentSlide;
    const AudioManager& rAudio;

    // int screenWidth, screenHeight;
    
    const std::vector<std::string> spritePaths = {"Sprites/idleTileSheet.png", "Sprites/runTileSheet.png", "Sprites/idleTileSheet_dmg.png", "Sprites/runTileSheet_dmg.png"};
    SpriteRenderer renderer = SpriteRenderer(spritePaths, position);

    ///// Animations
    // Indexes for the sprites that are used for animations
    const short idleAnim = 0;
    const short runAnim = 1;
    const short dmgIdleAnim = 2;
    const short dmgRunAnim = 3;
    const short fallAnim = 4;
    const short dmgFallAnim = 5;
    void UpdateAnimation();
    
    const float runAnimSpeed = .125f;
    const float idleAnimSpeed = .35f;
    
    Vector2 GetPosition() const { return position; }

    void Propel(Vector2 dir, float force);
    
    void Collisions();
    void Move(float deltaTime);
    void Deceleration(float deltaTime);
    void UpdateRectangle();

    void CoyoteTime(float deltaTime);
    void Jump();
    
    void Pausing();
    
    // Detects whenever the player leaves the screen and moves the player and its objects to the next slide
    void SectionDetection();
    
    void Death();
    void DamageTimer(float deltaTime);
    
    SDL_FRect rect;
    
    PlayerController controller;
    bool paused;

    //////////// Weapons
    WeaponController wc = WeaponController(this);
    
    
    //////////// Movement
    bool canMove = true;
    short direction = 0;

    bool setFloatTimer;
    const float floatDuration = .5f;
    float floatTimer;
    
    
    ////// Acceleration/Deceleration
    const float accelerationRate = 115;
    float moveSpeed = .9f;
    const float maxMoveSpeed = 10;
    
    bool decelerating;
    
    ////// Jumping
    bool jumping;
    bool jumpBuffer;
    const float airControl = 5.5f;
    const float jumpHeight = 5;
    const float jumpForce = 20;

    const float coyoteDuration = .2f;
    float coyoteTimer;


    ////// Health/Damage
    bool dead;
    const short maxHealth = 3;
    short health = maxHealth;
    bool respawning;

    bool isDamaged;
    const float dmgCooldown = 1.5f;
    float dmgTimer;
};
