#pragma once

#include "HealthManager.h" 
#include "SpriteRenderer.h"
#include "Collider.h"

class Character: public Collision
{
public:
    Character();
    ~Character();

    virtual void Update(float deltaTime);

    
    void GainHealth();
    void TakeDamage(float intensity);
    void Death();



protected:
    void ConfigureRenderer(const char* paths[], short frameCount = 3);
    virtual SpriteRenderer& GetRenderer() { return renderer; }

    Vector2 position;
    
    HealthManager health;

private:
    SpriteRenderer renderer;
};