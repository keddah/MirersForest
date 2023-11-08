#pragma once

#include "HealthManager.h" 
#include "SpriteRenderer.h"
#include "Collider.h"

class Character: public Collision
{
public:
    Character();
    ~Character();

    void Draw();

    void GainHealth();
    void TakeDamge(float intensity);
    void Death();


protected:
    HealthManager health = HealthManager();

private:
    SpriteRenderer renderer;
};