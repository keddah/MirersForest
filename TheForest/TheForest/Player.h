#pragma once

#include "GameCharacter.h"
#include "MovementController.h"
#include "PlayerController.h"
#include "WeaponController.h"

class Player : public Character
{
public:
    Player();
    ~Player();
    void Update(double deltaTime);

    void GivePowerup();

    PlayerController Controller();
    
private:
    void GainHealth();
    void TakeDamage(float damageIntensity);
    void Death();

    PlayerController controller = PlayerController();
    MovementController moveController = MovementController(this);
    WeaponController weaponController = MovementController(this);
};
