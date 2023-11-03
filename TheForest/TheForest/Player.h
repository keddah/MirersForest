#pragma once

#include "GameCharacter.h"

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

};