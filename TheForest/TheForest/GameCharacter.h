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

    void ConfigureRenderer(std::vector<const char*> paths, SDL_Rect source, SDL_Rect destination);


protected:
    HealthManager health = HealthManager();

private:
    void ConfigureRenderer();


    SpriteRenderer renderer;

};