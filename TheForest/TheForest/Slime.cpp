#include "Slime.h"

Slime::Slime(Player& plyr, std::vector<Tile>& floorRef, const AudioManager& sound): rTiles(floorRef), rPlayer(plyr), rAudio(sound)
{
    maxSpeed = 20;
    maxFallSpeed = 50;
    
    renderer.SetFrameCount(6);
    renderer.SetAnimSpeed(.225f);

    deathRenderer.SetFrameCount(11);
    deathRenderer.SetAnimSpeed(.05f);
}

void Slime::Update(float deltaTime)
{
    vfxPos = {position.x, position.y - 30 };
    if(dead || dying) return;
    
    ApplyGravity(true);
    Collisions();

    // Once all the movements have been done... add the velocity to the position
    // and update everything that needs to know.
    position += velocity;
    
    UpdateRectangle();

    HitPlayer();
    
    Death();

    // Patrol(deltaTime);
}

void Slime::Collisions()
{
    const Vector2 predictedPosX = position + Vector2(velocity.x, 0);
    const Vector2 predictedPosY = position + Vector2(0, velocity.y);
    const auto predictedRectX = SDL_FRect{ predictedPosX.x, predictedPosX.y, renderer.GetDrawSize().x, renderer.GetDrawSize().y };
    const auto predictedRectY = SDL_FRect{predictedPosY.x, predictedPosY.y, renderer.GetDrawSize().x, renderer.GetDrawSize().y};

    grounded = false;
    for (auto& tile : rTiles)
    {
        if(tile.GetLevelSlide() != levelSlide) continue;
        
        // Getting the rect of the tile doesn't work since its position is a reference (?) have to get it's size and position separetly.
        const SDL_FRect tileRect = SDL_FRect{ tile.GetRenderer().GetPosition().x, tile.GetRenderer().GetPosition().y, tile.GetRenderer().GetDrawSize().x, tile.GetRenderer().GetDrawSize().y};
        
        // Separate the axis collisions.
        const bool predictedCollisionX = SDL_HasIntersectionF(&predictedRectX, &tileRect);
        const bool predictedCollisionY = SDL_HasIntersectionF(&predictedRectY, &tileRect);

        if (predictedCollisionX)
        {
            velocity = Vector2(0, velocity.y);
        }
        if (predictedCollisionY)
        {
            velocity = Vector2(velocity.x, 0);
            grounded = true;
        }

    }
}

void Slime::Patrol(float deltaTime)
{
    if(!canMove)
    {
        if(position.Compare(patrolPoints[patrolIndex], 200))
        {
            velocity.x = 0;
            NextPoint();
            canMove = false;
            
            patrolTimer += deltaTime;
            if(patrolTimer > waitTime) canMove = true;
            else return;
        }
    }

    renderer.SetFrameCount(4);
    renderer.ChangeSpriteSheet(1);
    velocity.x += patrolPoints[patrolIndex].x > position.x? -moveSpeed : moveSpeed;
}

void Slime::NextPoint()
{
    patrolIndex++;
    if(patrolIndex > sizeof(patrolPoints)) patrolIndex = 0;
}

void Slime::Death()
{
    for(auto& bullet: rPlayer.GetActiveBullets())
    {
        const SDL_FRect bulletRect = {bullet.GetPosition().x, bullet.GetPosition().y, bullet.GetRect().w, bullet.GetRect().h};
        const SDL_FRect fxRect = {bullet.GetPosition().x, bullet.GetPosition().y, bullet.GetVFX().GetDrawSize().x, bullet.GetVFX().GetDrawSize().y};
        const bool collision = (SDL_HasIntersectionF(&rect, &fxRect) && bullet.IsDying()) || SDL_HasIntersectionF(&rect, &bulletRect);
        
        if(collision)
        {
            const bool canKill = bullet.GetType() != Projectile::EWeaponTypes::Sun && (bullet.GetType() == Projectile::EWeaponTypes::Petal ||
                (bullet.GetType() == Projectile::EWeaponTypes::Seed && !bullet.IsSpecial()));
            
            if(canKill) bullet.Kill();
            
            rAudio.PlaySound(AudioManager::Esounds::SlimeDeath);
            dying = true;
        }
    }

    DeathAnimation();
}

void Slime::DeathAnimation()
{
    if(!dying) return;

    deathRenderer.PlayAnimation();

    // Once the animation finishes ... is animating = false - Stop drawing/updating after that happens
    if(!deathRenderer.IsAnimating()) dead = true;
}

void Slime::HitPlayer() const
{
    if(rPlayer.GetLevelSlide() != levelSlide) return;
    
    if(SDL_HasIntersectionF(&rPlayer.GetRect(), &rect)) rPlayer.TakeDamage();
}

void Slime::UpdateRectangle()
{
    const Vector2 playerSize = renderer.GetDrawSize();

    rect.x = position.x;
    rect.y = position.y;
    rect.w = playerSize.x;
    rect.h = playerSize.y;
}
