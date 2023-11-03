#pragma once


class Player
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