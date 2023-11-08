#pragma once

class HealthManager
{
public:
    HealthManager();
    //HealthManager(Character _owner);
    ~HealthManager();

    void TakeDamage(float damageIntensity);
    void GainHealth();

private:
    //Character Owner;

    float damageResistance = 1;

    const float maxLives = 3;
    float currentLives = maxLives;
};