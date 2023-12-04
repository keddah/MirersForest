#include "WeaponController.h"
#include "CustomTimer.h"


WeaponController::WeaponController(PlayerController& ctrl, const SDL_FRect& plyrPos) : controller(ctrl), playerRect(plyrPos)
{
}

void WeaponController::Update(float deltaTime)
{
    // Weapon selection needs to be ran before shooting.
    WeaponSelection();
    Shooting();
    
    for(auto& bullet : activeBullets) bullet.Update();
}

// Gets called just before projectiles are spawned...
void WeaponController::WeaponSelection()
{
    const bool special = controller.IsRMB();
    switch (selectedWeapon)
    {
        // Tuple order = Type->Force->Size->Delay->ammo
        case EWeaponTypes::Seed:
            weapon = std::make_tuple(selectedWeapon, (special? seedForce * 2 : seedForce), special? seedSize * 2 : seedSize, seedDelay, seedAmmo);
        break;
			
        case EWeaponTypes::Petal:
            weapon = std::make_tuple(selectedWeapon, petalForce, petalSize, special? petalDelay * 5: petalDelay, petalAmmo);
            break;
			    
        case EWeaponTypes::Sun:
            weapon = std::make_tuple(selectedWeapon, special? 0 : sunForce, sunSize, sunDelay, sunAmmo);
            break;
			    
        case EWeaponTypes::Thorn:
            weapon = std::make_tuple(selectedWeapon, thornForce, thornSize, thornDelay, thornAmmo);
            break;
    }
}

void WeaponController::Shooting()
{
    // If left dir = -1 ... otherwise ... if right dir = 1 ... otherwise dir = 0
    direction = controller.IsLeft()? -1 : (controller.IsRight()? 1: 0);
    
    // Update the projectile spawn position; 
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


    if(!(controller.IsLMB() || controller.IsRMB())) return;
    
    Projectile newBullet = Projectile(spawnPos, std::get<2>(weapon), controller.IsRMB());
    activeBullets.emplace_back(newBullet);
    
    canShoot = false;
}


void WeaponController::DrawBullets()
{
    for(auto& bullet : activeBullets) bullet.Draw();
}
