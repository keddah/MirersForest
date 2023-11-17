#define print(x) { std::cout<< x << std::endl; }

#pragma once

#include <array>
#include <string>

#include "HealthManager.h" 
#include "SpriteRenderer.h"
#include "Collider.h"

class Character: public Collision
{
public:
    Character(std::vector<std::string> paths, SDL_FRect& newRect);
    ~Character() = default;

    virtual void Update(float deltaTime);

    void GainHealth();
    void TakeDamage(float intensity);
    void Death();



protected:
    void ConfigureRenderer(std::vector<std::string> paths, short frameCount = 3);
    virtual SpriteRenderer& GetRenderer() { return renderer; }

    Vector2 position;
    
    SpriteRenderer renderer;
    
    HealthManager health;

private:
    void CheckCollisions();
    
};