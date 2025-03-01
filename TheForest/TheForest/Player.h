/**************************************************************************************************************
* Player - Header
*
* The header file for the Player class and the Weapon Controller class. Declares all of the functions and parameters that the player needs to function.
* This file also contains the Weapon Controller class which is a private class of the player.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

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
    ~Player() { renderer.DestroyAllTextures(); }
    
    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);

    // Draw weapons before drawing the player so that the arrow is behind the player.
    void Draw() { wc.Draw(); renderer.Draw(); }

    short GetLevelSlide() const { return rCurrentSlide; }

    void NextLevel() { finished = true; }
    
    bool Respawn(const bool force = false)
    {
        if(force) respawning = true;
        else respawning = controller.JumpBtnDown() && dead;
        return respawning;
    }
    bool IsRespawning() const { return respawning; }
    void Reset();
    void Unpause();
    void FinishLevel();

    bool GivePowerup();
    void TakeDamage();
    void Float();

    
////////////// Gets
    std::vector<Projectile>& GetActiveBullets() { return wc.GetActiveBullets(); }
    const SpriteRenderer& GetRenderer() const { return renderer; } 
    const SDL_FRect& GetRect() const { return rect; } 

    bool IsPaused() const { return paused; }

    bool IsFinished() const { return finished; }
    bool AbleToFinish() const { return canFinish; }
    
    bool IsDead() const { return dead; }
    void Kill() { dead = true; }
    
    ///// UI related
    float GetAmmo() const { return wc.GetAmmo(); }
    float GetMaxAmmo() const { return wc.GetMaxAmmo(); }
    short GetHealth() const { return health; }

    Vector2 GetMousePos() const { return controller.GetMousePosition(); }
    bool LMB() const { return controller.IsLMB(); }
    bool SpaceDown() const { return controller.JumpBtnDown(); }
    
    Projectile::EWeaponTypes GetType() const { return wc.GetType(); }
    
    float GetWeaponCooldown() const { return wc.GetCooldown(); }
    float GetShootTimer() const { return wc.GetShootTimer(); }
    
private:
    class WeaponController
    {
    public:
        WeaponController(Player* pP);
        ~WeaponController()
        {
            arrow.DestroyAllTextures();
            for(auto& bullet : activeBullets) bullet.Destroy();
            activeBullets.clear();
        }

        void Update(float deltaTime);
        void FixedUpdate(float deltaTime);
        void Draw();
        std::vector<Projectile>& GetActiveBullets() { return activeBullets; }

        Projectile::EWeaponTypes GetType() const { return std::get<0>(weapon); }
        
        float GetCooldown() const { return std::get<2>(weapon); }
        float GetShootTimer() const { return ammo == 0? 0 : shootTimer; }
        
        short GetAmmo() const { return ammo; }
        short GetMaxAmmo() const { return maxAmmo; }

        bool AmmoFull() const { return ammo == maxAmmo;  }
        void Refill() { ammo = maxAmmo;  }
        void KillBullets() { for (auto& bullet : activeBullets) bullet.Kill(); }

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
        float shootTimer = 0;
    
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

        // The force used to throw the projectiles
        const short seedForce = 16;
        const short petalForce = 12;
        const short sunForce = 32;
        // const int thornForce = 8;

        // The delay between each shot 
        const float seedDelay = .8f;
        const float petalDelay = .125f;
        const float sunDelay = 2;
        // const float thornDelay = 1.2f;

        // Gravity Multipliers
        const float seedGravity = .04f;
        const float petalGravity = .05f;
        const float sunGravity = 0;
        // const float thornGravity = .01f ;

        // The force that is used to propel the player whenever they're midair
        const float seedRepulsion = 3;
        const float petalRepulsion = 1.09f;
        const float sunRepulsion = 15;
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
    short& rCurrentSlide;
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
    const int accelerationRate = 240;
    float moveSpeed = 2.2f;
    const short maxMoveSpeed = 20;
    
    bool decelerating;
    
    ////// Jumping
    bool jumping;
    bool jumpBuffer;
    const short airControl = 5;
    const float jumpHeight = 11.5f;
    const float jumpForce = 35;

    const float coyoteDuration = .25f;
    float coyoteTimer;


    ////// Health/Damage
    bool dead;
    const short maxHealth = 3;
    short health = maxHealth;
    bool respawning;

    bool isDamaged;
    
    // In seconds
    const float dmgCooldown = 1.5f;
    float dmgTimer;

    bool finished = false;
    bool canFinish = false;
};
