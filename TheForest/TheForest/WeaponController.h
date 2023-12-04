#pragma once

#include <vector>
#include "Projectile.h"
#include "Controllers.h"

class WeaponController
{
public:
    WeaponController(PlayerController& ctrl, const SDL_FRect& plyrPos);
    ~WeaponController() = default;

    enum class EWeaponTypes
    {
        Seed,
        Petal,
        Sun,
        Thorn,
    };
	
    void Update(float deltaTime);
    void DrawBullets();

private:
    const SDL_FRect& playerRect;
    PlayerController& controller;

    void WeaponSelection();
    void Shooting();

    bool canShoot = true;
    float shootTimer;
    
    EWeaponTypes selectedWeapon = EWeaponTypes::Seed;

    std::vector<Projectile> activeBullets = std::vector<Projectile>();

    const int seedForce = 8;
    const int petalForce = 8;
    const int sunForce = 8;
    const int thornForce = 8;

    const float seedDelay = .8f;
    const float petalDelay = .125f;
    const float sunDelay = 2;
    const float thornDelay = 1.2f;

	
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

    // The weapon type .. The force .. The size .. The Delay .. The ammo count
    // When Getting :
    // Type = 0 .. Force = 1 .. Size = 2 .. Delay = 3 .. Ammo = 4
    std::tuple<EWeaponTypes, float, Vector2, float, short> weapon;
};