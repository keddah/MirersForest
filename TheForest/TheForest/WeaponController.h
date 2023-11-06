#pragma once
#include "Player.h"

class WeaponController
{
public:
    WeaponController(Player*& plyr);
    
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
};
