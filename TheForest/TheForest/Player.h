#pragma once

#include "GameCharacter.h" 

#include "Controllers.h"

class Player : public Character
{
public:
    Player() = default;
    Player(const std::vector<Collision*>& _otherColliders);
    ~Player() = default;
    void Update(float deltaTime) override;

    void ChangeMoveState(MovementController::EMovementState state);
    
    void GivePowerup();
    Vector2& GetPosition();
    PlayerController& Controller() { return controller; }
    MovementController& GetMoveController() { return moveController; } 
    
private:
    void GainHealth();
    void TakeDamage(float damageIntensity);
    void Death();
        
    const std::vector<Collision*>& otherColliders;

    PlayerController controller;
    MovementController moveController = MovementController(controller, *this, otherColliders);
    //WeaponController weaponController = WeaponController(controller, position);

    std::vector<std::string> animations
    {
        "Sprites/testspritesheet.png",
    };
};
