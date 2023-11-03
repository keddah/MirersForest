#pragma once

#include "GameCharacter.h"
#include "MovementController.h"

class Player : Character
{
public:
    Player();
    ~Player();

    void GivePowerup();

    void Update();
    void Draw();

private:

    void GainHealth();
    void TakeDamage();
    void Death();

    MovementController moveController = MovementController();
};