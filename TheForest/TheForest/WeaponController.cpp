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

    // print(activeBullets.size())
    
    for(int i = 0; i < activeBullets.size(); i++)
    {
        activeBullets[i].Update(deltaTime);
        activeBullets[i].Expire(deltaTime);
        
        if(activeBullets[i].IsDead())
        {
            // activeBullets[i].Kill();
            activeBullets.erase(activeBullets.begin() + i);
        }
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
            weapon = std::make_tuple(selectedWeapon, sunForce, sunDelay, sunAmmo, sunGravity, special? 0 : sunRepulsion);
            break;
			    
        case Projectile::EWeaponTypes::Thorn:
            weapon = std::make_tuple(selectedWeapon, thornForce, thornDelay, thornAmmo, thornGravity, thornRepulsion);
            break;
    }
}


/////////////////// BUGS
/// projectiles are deleted too early (their lifespan)
/// shotgun doesn'w work properly once the mouse goes past a certain angle


void Player::WeaponController::Shooting()
{
    // Update the projectile spawn position;
    const SDL_FRect& spawnRect = arrow.GetRect();
    
    // The offsets are different for straight-moving projectiles 
    if(std::get<0>(weapon) == Projectile::EWeaponTypes::Thorn || std::get<0>(weapon) == Projectile::EWeaponTypes::Sun)
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

    if(thisPlayer.controller.IsRMB() && selectedWeapon == Projectile::EWeaponTypes::Petal)
    {
        Shotgun();
        return;
    }
    
    if(!(thisPlayer.controller.IsLMB() || thisPlayer.controller.IsRMB())) return;

    // Since the projectile is so big it spawns in the ground and instantly blows up.
    const bool bigSeed = std::get<0>(weapon) == Projectile::EWeaponTypes::Seed && thisPlayer.controller.IsRMB();

    // Spawn the projectile higher if it's the big seed.
    const Projectile newBullet = Projectile(weapon, bigSeed? Vector2(spawnPos.x, spawnPos.y - 20): spawnPos, GetShootAngle(), thisPlayer.velocity, thisPlayer.controller.IsRMB(), thisPlayer.floor);
    activeBullets.push_back(newBullet);
    
    canShoot = false;

    thisPlayer.Propel(newBullet.GetRepulsion(), std::get<5>(weapon));
    if(std::get<0>(weapon) == Projectile::EWeaponTypes::Sun && thisPlayer.controller.IsRMB()) thisPlayer.Float();
}

void Player::WeaponController::Shotgun()
{
    for(int i = 0; i < 9; i++)
    {
        constexpr float pelletSpread = .1f;
        const float shootAngle = GetShootAngle() - (GetShootAngle() < 0? i  : -i) * pelletSpread;

        // Re setting the weapon so that the pellets at the top of the cone go further than the ones at the bottom
        weapon = std::make_tuple(selectedWeapon, petalForce + i, petalDelay * 10, petalAmmo, petalGravity, petalRepulsion);
        
        Projectile petal = Projectile(weapon, spawnPos, shootAngle, thisPlayer.velocity, thisPlayer.controller.IsRMB(),thisPlayer.floor);
        activeBullets.emplace_back(petal);

        // The player is launched using x times more to simulate each petal giving its own additional force
        thisPlayer.Propel(petal.GetRepulsion(), std::get<5>(weapon) * 9);
    }

    canShoot = false;
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
