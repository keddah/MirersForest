/**************************************************************************************************************
* Weapon Controller - Code
*
* The code file for the Weapon controller class. Responsible for handling everything weapons related.
* Spawns projectiles... uses the player reference to get the mouse position. Also responsible for updating and drawing
* all of the projectiles that it creates. Since this is a private class of the player it can access all of the player's private members.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#include "Player.h"


Player::WeaponController::WeaponController(Player* pP) : rP(*pP)
{
    arrow.SetSpritePivot({arrow.GetRect().w/2, arrow.GetRect().h - 5});
}

void Player::WeaponController::FixedUpdate(float deltaTime)
{
    // Everything movement related
    for(auto& bullet : activeBullets)
    {
        bullet.FixedUpdate();
        bullet.Beam(deltaTime, rP.controller.GetMousePosition());
    }
}

void Player::WeaponController::Update(float deltaTime)
{
    arrowPos = {(rP.rect.x + rP.rect.w / 2) - arrow.GetRect().w / 2, rP.rect.y - rP.rect.h };

    UpdateBullets(deltaTime);
    
    // Weapon selection needs to be ran before shooting.
    ConfigureWeapon();
    WeaponSelection();

    // Needs to be ran after weapon selection
    Shooting(deltaTime);
}

void Player::WeaponController::UpdateBullets(float deltaTime)
{
    for(int i = 0; i < activeBullets.size(); i++)
    {
        activeBullets[i].Update(deltaTime);
        activeBullets[i].Expire(deltaTime);

        // Sound that plays on projectile impacts
        if((activeBullets.end() - 1)->IsDying())
        {
            if(!(activeBullets.end() - 1)->sfxPlaying)
            {
                rP.rAudio.PlaySound(AudioManager::Esounds::ProjImpact);
                if((activeBullets.end() - 1)->GetType() == Projectile::EWeaponTypes::Seed && (activeBullets.end() - 1)->IsSpecial()) rP.rAudio.PlaySound(AudioManager::Esounds::SeedExplosion);
                if((activeBullets.end() - 1)->GetType() == Projectile::EWeaponTypes::Sun && (activeBullets.end() - 1)->IsSpecial()) rP.rAudio.PlaySound(AudioManager::Esounds::BeamStrike);
                (activeBullets.end() - 1)->sfxPlaying = true;
            }
        }
        
        // (Done like this since the shotgun projectiles are spawned backwards....
        if((activeBullets.end() - 1)->IsDead())
        {
            if(activeBullets[i].GetType() == Projectile::EWeaponTypes::Seed && activeBullets[i].IsSpecial()) rP.rAudio.PlaySound(AudioManager::Esounds::SeedExplosion);
            rP.rAudio.PlaySound(AudioManager::Esounds::ProjImpact);
            activeBullets.erase(activeBullets.end() - 1);
            break;
        }
    }
}

void Player::WeaponController::WeaponSelection()
{
    if(rP.controller.WheelUp()) PreviousWeapon();
    else if(rP.controller.WheelDown()) NextWeapon();

    else if(rP.controller.OnePressed()) selectedWeapon = Projectile::EWeaponTypes::Seed;
    else if(rP.controller.TwoPressed()) selectedWeapon = Projectile::EWeaponTypes::Petal;
    else if(rP.controller.ThreePressed()) selectedWeapon = Projectile::EWeaponTypes::Sun;
    // else if(thisPlayer.controller.FourPressed()) selectedWeapon = Projectile::EWeaponTypes::Thorn;

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

        // case Projectile::EWeaponTypes::Thorn:
        //     arrow.ChangeSpriteSheet(3);
        //     break;
    }
}

// Gets called just before projectiles are spawned...
void Player::WeaponController::ConfigureWeapon()
{
    const bool special = rP.controller.IsRMB();
    switch (selectedWeapon)
    {
        // Tuple order = Type->Force->Size->Delay->AmmoCost->Gravity
    case Projectile::EWeaponTypes::Seed:
            weapon = std::make_tuple(selectedWeapon, (special? seedForce * .8f : seedForce), seedDelay, special? seedCost * 2 : seedCost, seedGravity, special? seedRepulsion * 1.4f : seedRepulsion);
        break;
			
        case Projectile::EWeaponTypes::Petal:
            weapon = std::make_tuple(selectedWeapon, petalForce, special? petalDelay * 8: petalDelay, petalCost, petalGravity, petalRepulsion);
            break;
			    
    case Projectile::EWeaponTypes::Sun:
            weapon = std::make_tuple(selectedWeapon, sunForce, sunDelay, special? sunCost * 2 : sunCost, sunGravity, special? 0 : sunRepulsion);
            break;
			    
        // case Projectile::EWeaponTypes::Thorn:
        //     weapon = std::make_tuple(selectedWeapon, thornForce, thornDelay, thornAmmo, thornGravity, thornRepulsion);
        //     break;
    }
}

void Player::WeaponController::Shooting(float deltaTime)
{
    //\\//\\//\\//\\// Bullet Availability //\\//\\//\\//\\//
    if(!canShoot)
    {
        shootTimer += deltaTime;
        if(shootTimer > std::get<2>(weapon))
        {
            shootTimer = 0;
            canShoot = true;
        }
    }
    
    // print(ammo)
    if(ammo <= 0)
    {
        // Play the sound whenever the mouse is clicked
        if(canShoot && (rP.controller.IsLMB() || rP.controller.IsRMB())) rP.rAudio.PlaySound(AudioManager::Esounds::NoAmmo);
        
        canShoot = false;
        ammo = 0;

        return;
    }


    //\\//\\//\\//\\// Setting Spawn //\\//\\//\\//\\//

    // Update the projectile spawn position;
    const SDL_FRect& spawnRect = arrow.GetRect();
    
    // The offsets are different for straight-moving projectiles 
    if(std::get<0>(weapon) == Projectile::EWeaponTypes::Sun)
    {
        spawnPos = {spawnRect.x + spawnOffset.x, spawnRect.y + spawnOffset.y};
    }
    else spawnPos = {rP.rect.x  +rP.rect.w / 2, rP.rect.y + rP.rect.h / 2 };


    //\\//\\//\\//\\// Actual Shooting //\\//\\//\\//\\//

    if(!canShoot) return;

    const bool special = rP.controller.IsRMB();
    
    if(special && selectedWeapon == Projectile::EWeaponTypes::Petal)
    {
        Shotgun();
        return;
    }

    // When shoot is pressed.....
    if(!(rP.controller.IsLMB() || special)) return;

    
    // The special projectile have different spawns...
    Vector2 pos;
    switch (std::get<0>(weapon))
    {
        case Projectile::EWeaponTypes::Seed:
            // Since the projectile is so big it spawns in the ground and instantly blows up.
            if(special) pos = {spawnPos.x, spawnPos.y - 20};
            break;
        
        case Projectile::EWeaponTypes::Petal:
            break;
        
        case Projectile::EWeaponTypes::Sun:
            if(special)
            {
                pos = {rP.position.x - 300, rP.position.y - 50};

                // The Sun's special causes the player to lose their velocity.
                rP.Float();
            }
            break;
    }
    if(!special) pos = spawnPos;
    
    // Spawn the projectile higher if it's the big seed.
    const Projectile newBullet = Projectile(weapon, pos, GetShootAngle(), rP.velocity, special, rP.tiles);
    activeBullets.push_back(newBullet);

    ammo -= std::get<3>(weapon);
    
    canShoot = false;

    if(!canShoot)
    {
        switch (std::get<0>(weapon))
        {
        case Projectile::EWeaponTypes::Seed:
            rP.rAudio.PlaySound(AudioManager::Esounds::SeedShoot);
            break;
            
        case Projectile::EWeaponTypes::Petal:
            rP.rAudio.PlaySound(AudioManager::Esounds::PetalShoot);
            break;
            
        case Projectile::EWeaponTypes::Sun:
            if(special) rP.rAudio.PlaySound(AudioManager::Esounds::SunBeam);
            else rP.rAudio.PlaySound(AudioManager::Esounds::SunShoot);
            break;
        }
    }
    
    rP.Propel(newBullet.GetRepulsion(), std::get<5>(weapon));
}

void Player::WeaponController::Shotgun()
{
    constexpr short pellets = 8;
    constexpr short midPoint = pellets / 2;

    // if the arrow is pointing to the right
    const bool correction = arrow.GetRenderAngle() > 0 && arrow.GetRenderAngle() < 180; 

    float repulsion_x = 0;
    float repulsion_y = 0;
    
    for(short i = 0; i < pellets; i++)
    {
        constexpr float pelletSpread = 10;

        // Flip the the pellet spawn if the arrow is pointing to the right (to fix it)...
        const float shootAngle = correction? -(GetShootAngle() - (midPoint - i) / pelletSpread) + GetShootAngle() * 2 : GetShootAngle() + (-midPoint + i) / pelletSpread;
        
        // Re setting the weapon so that the pellets at the top of the cone go further than the ones at the bottom
        weapon = std::make_tuple(selectedWeapon, petalForce + i, petalDelay * 10, petalCost, petalGravity, petalRepulsion);
        
        Projectile petal = Projectile(weapon, spawnPos, shootAngle, rP.velocity, rP.controller.IsRMB(),rP.tiles);
        activeBullets.emplace_back(petal);
        
        ammo -= std::get<3>(weapon);

        repulsion_x += petal.GetRepulsion().x;
        repulsion_y += petal.GetRepulsion().y;
    }
    
    // Getting the average repulsion direction and multiplying by how many pellets there are to simulate each pellet applying force
    // simultaneously
    rP.Propel(Vector2(repulsion_x / pellets, repulsion_y / pellets), std::get<5>(weapon) * pellets);

    canShoot = false;
    if(!canShoot)
    {
        for(int i = 0; i < pellets; i++)
        {
            rP.rAudio.PlaySound(AudioManager::Esounds::PetalShoot);
        }
    }
}

float Player::WeaponController::GetShootAngle() const
{
    const Vector2 mouse = rP.controller.GetMousePosition();
    const Vector2 difference = mouse - rP.position;
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
            selectedWeapon = Projectile::EWeaponTypes::Seed;
            break;

        // case Projectile::EWeaponTypes::Thorn:
        //     selectedWeapon = Projectile::EWeaponTypes::Seed;
        //     break;
    }
}

void Player::WeaponController::PreviousWeapon()
{
    switch (selectedWeapon)
    {
    case Projectile::EWeaponTypes::Seed:
        selectedWeapon = Projectile::EWeaponTypes::Sun;
        break;

    case Projectile::EWeaponTypes::Petal:
        selectedWeapon = Projectile::EWeaponTypes::Seed;
        break;

    case Projectile::EWeaponTypes::Sun:
        selectedWeapon = Projectile::EWeaponTypes::Petal;
        break;

    // case Projectile::EWeaponTypes::Thorn:
    //     selectedWeapon = Projectile::EWeaponTypes::Sun;
    //     break;
    }
}

void Player::WeaponController::Draw()
{
    // Have to convert from radians to degrees .... + (whatever number because the arrow is off)
    if(!rP.IsPaused()) arrow.SetRenderAngle(static_cast<float>((GetShootAngle() * 180/std::_Pi) + arrowOffset));
    arrow.Draw();
    for(auto& bullet : activeBullets)
    {
        bullet.Draw();
        bullet.DeathAnimation(false);
    }
}
