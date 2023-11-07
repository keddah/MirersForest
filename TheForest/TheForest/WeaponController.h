#pragma once
#include "Player.h"

class WeaponController
{
public:
    WeaponController(Player* plyr);
    ~WeaponController();

    void Update(double deltaTime);
    
    
private:
    Player* player;

    enum WeaponType
    {
        Normal,
        CloseRange,
        Sniper,
        Melee
    };

    short currentWeapon = Normal;
    
    // Projectile spawn position
    Vector2 spawnPos;

    // std::vector<> projectiles = ;
};
