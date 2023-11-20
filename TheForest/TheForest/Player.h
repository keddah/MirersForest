#pragma once

#include "GameCharacter.h" //ok

#include "Controllers.h"

class Player : public Character
{
public:
    Player() = default;
    Player(const std::vector<Collision*>& otherColliders);
    ~Player() = default;
    void Update(float deltaTime) override;

    void ChangeMoveState(MovementController::EMovementState state);
    
    void GivePowerup();
    Vector2& GetPosition();
    PlayerController& Controller() { return controller; }
    MovementController& GetMoveController() { return moveController; } 
    SpriteRenderer& GetRenderer() override { return Character::GetRenderer(); }
    
private:
    void GainHealth();
    void TakeDamage(float damageIntensity);
    void Death();

    PlayerController controller;
    MovementController moveController = MovementController(controller, position, blockingDirections);
    WeaponController weaponController = WeaponController(controller, position);

    std::vector<std::string> animations
    {
        "Sprites/testspritesheet.png",
    };
};
