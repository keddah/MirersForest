#include "Player.h"
#include "CustomTimer.h"


Player::WeaponController::WeaponController(Player* plyr) : thisPlayer(*plyr)
{
}

void Player::WeaponController::Update(float deltaTime)
{
    GetShootAngle();
    
    // Weapon selection needs to be ran before shooting.
    WeaponSelection();
    Shooting();
    
    for(auto& bullet : activeBullets) bullet.Update();
}

// Gets called just before projectiles are spawned...
void Player::WeaponController::WeaponSelection()
{
    const bool special = thisPlayer.controller.IsRMB();
    switch (selectedWeapon)
    {
        // Tuple order = Type->Force->Size->Delay->ammo->gravity
        case Projectile::EWeaponTypes::Seed:
            weapon = std::make_tuple(selectedWeapon, (special? seedForce * 2 : seedForce), special? seedSize * 2 : seedSize, seedDelay, seedAmmo, seedGravity, seedRepulsion);
        break;
			
        case Projectile::EWeaponTypes::Petal:
            weapon = std::make_tuple(selectedWeapon, petalForce, petalSize, special? petalDelay * 5: petalDelay, petalAmmo, petalGravity, petalRepulsion);
            break;
			    
        case Projectile::EWeaponTypes::Sun:
            weapon = std::make_tuple(selectedWeapon, special? 0 : sunForce, sunSize, sunDelay, sunAmmo, sunGravity, sunRepulsion);
            break;
			    
        case Projectile::EWeaponTypes::Thorn:
            weapon = std::make_tuple(selectedWeapon, thornForce, thornSize, thornDelay, thornAmmo, thornGravity, thornRepulsion);
            break;
    }
}

void Player::WeaponController::Shooting()
{
    // If left dir = -1 ... otherwise ... if right dir = 1 ... otherwise dir = 0
    direction = thisPlayer.controller.IsLeft()? -1 : (thisPlayer.controller.IsRight()? 1: 0);
    
    // Update the projectile spawn position;
    const SDL_FRect& playerRect = thisPlayer.rect;
    spawnPos = Vector2(playerRect.x + playerRect.w/2, playerRect.y + playerRect.h/2) + Vector2(direction * projSpawnOffset, 0);
    
    if(!canShoot)
    {
        shootTimer += Time::GetDeltaTime();
        if(shootTimer > std::get<3>(weapon))
        {
            shootTimer = 0;
            canShoot = true;
        }
        
        return;
    }


    if(!(thisPlayer.controller.IsLMB() || thisPlayer.controller.IsRMB())) return;
    
    Projectile newBullet = Projectile(weapon, spawnPos, GetShootAngle(), thisPlayer.velocity, thisPlayer.controller.IsRMB());
    activeBullets.emplace_back(newBullet);
    
    canShoot = false;

    thisPlayer.Propel(newBullet.GetRepulsion(), std::get<6>(weapon));
}

float Player::WeaponController::GetShootAngle() const
{
    const Vector2 mouse = thisPlayer.controller.GetMousePosition();
    const Vector2 difference = mouse - thisPlayer.position;
    const float rot = atan2(difference.y, difference.x);

    return rot;
}


void Player::WeaponController::DrawBullets()
{
    for(auto& bullet : activeBullets) bullet.Draw();
}
