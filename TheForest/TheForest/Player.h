#pragma once

#include "GameCharacter.h" //ok

#include "Controllers.h"

class Player : public Character
{
public:
    Player();
    ~Player();
    void Update(float deltaTime) override;

    void ChangeMoveState(MovementController::EMovementState state);
    
    void GivePowerup();
    Vector2& GetPosition();
    PlayerController& Controller();
    SpriteRenderer& GetRenderer() override;
    
private:
    void GainHealth();
    void TakeDamage(float damageIntensity);
    void Death();

    PlayerController controller;
    MovementController moveController = MovementController(controller, position);
    WeaponController weaponController = WeaponController(controller, position);
};
