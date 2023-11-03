#pragma once

#include <vector>

#include "GameCharacter.h"
#include "MovementController.h"
#include "PlayerController.h"

class Player : Character
{
public:
    Player();
    ~Player();

    void GivePowerup();

    void Update(double deltaTime);

private:
    void GainHealth();
    void TakeDamage(float damageIntensity);
    void Death();

    PlayerController controller = PlayerController();
    MovementController moveController = MovementController();
};