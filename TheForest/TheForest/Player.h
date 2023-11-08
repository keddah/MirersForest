#pragma once

#include "GameCharacter.h" //ok

#include "WeaponController.h"
#include "MovementController.h"

class Player : public Character
{
public:
    Player();
    ~Player();
    virtual void Update(float deltaTime);
    virtual void Draw();

    void GivePowerup();
    Vector2& GetPosition();

    PlayerController Controller();
    
private:
    void GainHealth();
    void TakeDamage(float damageIntensity);
    void Death();

    Vector2 position;

    PlayerController controller;
    MovementController moveController = MovementController(controller, position);
    WeaponController weaponController = WeaponController(controller, position);
};
