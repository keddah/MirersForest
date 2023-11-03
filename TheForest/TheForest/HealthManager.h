#pragma once

class HealthManager
{
public:
    HealthManager();
    ~HealthManager();

    void TakeDamage();
    void GainHealth();

private:
    const short maxLives = 3;
    short currentLives = maxLives;
};