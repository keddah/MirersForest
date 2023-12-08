#include "Player.h"
#include "CustomTimer.h"


Player::WeaponController::WeaponController(Player* plyr) : thisPlayer(*plyr)
{
    arrow.SetSpritePivot({arrow.GetRect().w/2, arrow.GetRect().h - 5});
}

void Player::WeaponController::Update(float deltaTime)
{
    arrowPos = {(thisPlayer.rect.x + thisPlayer.rect.w / 2) - arrow.GetRect().w / 2, thisPlayer.rect.y - thisPlayer.rect.h };

    WeaponSelection();
    
    // Weapon selection needs to be ran before shooting.
    ConfigureWeapon();
    Shooting();

    print(activeBullets.size())
    
    for(int i = 0; i < activeBullets.size(); i++)
    {
        activeBullets[i].Update();

        
        activeBullets[i].Expire(deltaTime);
        if(activeBullets[i].IsDead()) activeBullets.erase(activeBullets.begin());
    }
}

void Player::WeaponController::WeaponSelection()
{
    if(thisPlayer.controller.WheelUp()) PreviousWeapon();
    else if(thisPlayer.controller.WheelDown()) NextWeapon();

    else if(thisPlayer.controller.OnePressed()) selectedWeapon = Projectile::EWeaponTypes::Seed;
    else if(thisPlayer.controller.TwoPressed()) selectedWeapon = Projectile::EWeaponTypes::Petal;
    else if(thisPlayer.controller.ThreePressed()) selectedWeapon = Projectile::EWeaponTypes::Sun;
    else if(thisPlayer.controller.FourPressed()) selectedWeapon = Projectile::EWeaponTypes::Thorn;

    switch (selectedWeapon)
    {
        case Projectile::EWeaponTypes::Seed:
            arrow.ChangeSpriteSheet(0);
            break;

        case Projectile::EWeaponTypes::Petal:
            arrow.ChangeSpriteSheet(1);
            break;

        case Projectile::EWeaponTypes::Sun:
            arrow.ChangeSpriteSheet(2);
            break;

        case Projectile::EWeaponTypes::Thorn:
            arrow.ChangeSpriteSheet(3);
            break;
    }
}

// Gets called just before projectiles are spawned...
void Player::WeaponController::ConfigureWeapon()
{
    const bool special = thisPlayer.controller.IsRMB();
    switch (selectedWeapon)
    {
        // Tuple order = Type->Force->Size->Delay->ammo->gravity
        case Projectile::EWeaponTypes::Seed:
            weapon = std::make_tuple(selectedWeapon, (special? seedForce * .8f : seedForce), seedDelay, seedAmmo, seedGravity, seedRepulsion);
        break;
			
        case Projectile::EWeaponTypes::Petal:
            weapon = std::make_tuple(selectedWeapon, petalForce, special? petalDelay * 5: petalDelay, petalAmmo, petalGravity, petalRepulsion);
            break;
			    
        case Projectile::EWeaponTypes::Sun:
            weapon = std::make_tuple(selectedWeapon, special? 0 : sunForce, sunDelay, sunAmmo, sunGravity, sunRepulsion);
            break;
			    
        case Projectile::EWeaponTypes::Thorn:
            weapon = std::make_tuple(selectedWeapon, thornForce, thornDelay, thornAmmo, thornGravity, thornRepulsion);
            break;
    }
}

void Player::WeaponController::Shooting()
{
    // If left dir = -1 ... otherwise ... if right dir = 1 ... otherwise dir = 0
    direction = thisPlayer.controller.IsLeft()? -1 : (thisPlayer.controller.IsRight()? 1: 0);
    
    // Update the projectile spawn position;
    const SDL_FRect& spawnRect = arrow.GetRect();
    
    // The offsets are different for straight-moving projectiles 
    if(std::get<0>(weapon) == Projectile::EWeaponTypes::Thorn ||std::get<0>(weapon) == Projectile::EWeaponTypes::Sun)
    {
        spawnPos = {spawnRect.x + spawnOffset.x, spawnRect.y + spawnOffset.y};
    }
    else
    {
        spawnPos = {thisPlayer.rect.x  +thisPlayer.rect.w / 2, thisPlayer.rect.y + thisPlayer.rect.h / 2 };
    }
    
    if(!canShoot)
    {
        shootTimer += Time::GetDeltaTime();
        if(shootTimer > std::get<2>(weapon))
        {
            shootTimer = 0;
            canShoot = true;
        }
        
        return;
    }


    if(thisPlayer.controller.IsRMB())
    {
        SpecialShoot();
        return;
    }
    
    if(!thisPlayer.controller.IsLMB()) return;

    Projectile newBullet = Projectile(weapon, spawnPos, GetShootAngle(), thisPlayer.velocity, thisPlayer.controller.IsRMB());
    activeBullets.emplace_back(newBullet);
    
    canShoot = false;

    thisPlayer.Propel(newBullet.GetRepulsion(), std::get<5>(weapon));
}

void Player::WeaponController::SpecialShoot()
{
    switch (selectedWeapon)
    {
        case Projectile::EWeaponTypes::Seed:
            // Projectile seed = Projectile(weapon, spawnPos, GetShootAngle(), thisPlayer.velocity, thisPlayer.controller.IsRMB());
            // activeBullets.emplace_back(seed);
            // canShoot = false;
            // thisPlayer.Propel(seed.GetRepulsion(), std::get<5>(weapon));
            break;
        
        case Projectile::EWeaponTypes::Petal:
            for(int i = 0; i < 9; i++)
            {
                constexpr float pelletSpread = .1f;
                const float shootAngle = GetShootAngle() - (GetShootAngle() > 180? i : GetShootAngle() < 0? -i: i) * pelletSpread;

                // Re setting the weapon so that the pellets at the top of the cone go further than the ones at the bottom
                weapon = std::make_tuple(selectedWeapon, petalForce + i, petalDelay * 10, petalAmmo, petalGravity, petalRepulsion);
                
                Projectile petal = Projectile(weapon, spawnPos, shootAngle, thisPlayer.velocity, thisPlayer.controller.IsRMB());
                activeBullets.emplace_back(petal);

                // The player is launched using x times more to simulate each petal giving its own additional force
                thisPlayer.Propel(petal.GetRepulsion(), std::get<5>(weapon) * 9);
            }
        
            canShoot = false;
            break;
        
        case Projectile::EWeaponTypes::Sun:
            
            break;
        case Projectile::EWeaponTypes::Thorn:
            
            break;
    }
}

float Player::WeaponController::GetShootAngle() const
{
    const Vector2 mouse = thisPlayer.controller.GetMousePosition();
    const Vector2 difference = mouse - thisPlayer.position;
    const float rot = atan2(difference.y, difference.x);

    return rot;
}

void Player::WeaponController::NextWeapon()
{
    switch (selectedWeapon)
    {
        case Projectile::EWeaponTypes::Seed:
            selectedWeapon = Projectile::EWeaponTypes::Petal;
            break;

        case Projectile::EWeaponTypes::Petal:
            selectedWeapon = Projectile::EWeaponTypes::Sun;
            break;

        case Projectile::EWeaponTypes::Sun:
            selectedWeapon = Projectile::EWeaponTypes::Thorn;
            break;

        case Projectile::EWeaponTypes::Thorn:
            selectedWeapon = Projectile::EWeaponTypes::Seed;
            break;
    }
}

void Player::WeaponController::PreviousWeapon()
{
    switch (selectedWeapon)
    {
    case Projectile::EWeaponTypes::Seed:
        selectedWeapon = Projectile::EWeaponTypes::Thorn;
        break;

    case Projectile::EWeaponTypes::Petal:
        selectedWeapon = Projectile::EWeaponTypes::Seed;
        break;

    case Projectile::EWeaponTypes::Sun:
        selectedWeapon = Projectile::EWeaponTypes::Petal;
        break;

    case Projectile::EWeaponTypes::Thorn:
        selectedWeapon = Projectile::EWeaponTypes::Sun;
        break;
    }
}


void Player::WeaponController::Draw()
{
    // Have to convert from radians to degrees .... + (whatever number because the arrow is off)
    arrow.SetRenderAngle((GetShootAngle() * 180/std::_Pi) + arrowOffset);
    arrow.Draw();
    for(auto& bullet : activeBullets) bullet.Draw();
}
