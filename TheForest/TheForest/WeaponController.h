#pragma once

#include "Vector2.h"
#include "PlayerController.h" 

class WeaponController
{
public:
    WeaponController(PlayerController& ctrl, Vector2& plyrPos);
    ~WeaponController();

    void Update(float deltaTime);
    
    
private:
    PlayerController& controller;
    
    enum WeaponType
    {
        Normal,
        CloseRange,
        Sniper,
        Melee
    };

    short currentWeapon = Normal;
    
    Vector2& playerPosition;
    // Projectile spawn position
    Vector2 spawnPos = Vector2();

    // std::vector<> projectiles = ;
};
