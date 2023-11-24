#define print(x) { std::cout<< x << std::endl; }

#pragma once

#include <string>

#include "HealthManager.h" 
#include "Collider.h"

class Character: public Collision
{
public:
    Character(const std::vector<std::string>& paths, SDL_FRect& newRect, const std::vector<Collision*>& colliders);
    virtual ~Character() = default;

    virtual void Update(float deltaTime);

    void GainHealth();
    void TakeDamage(float intensity);
    void Death();



protected:
    void SetFrameCount(short frameCount = 3);

    HealthManager health;

private:
    void CheckCollisions();
    
};