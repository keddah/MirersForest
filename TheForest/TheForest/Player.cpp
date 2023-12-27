/**************************************************************************************************************
* Player - Code
*
* The code file for the Player class. Responsible for giving functionality to the player. Manages player collisions, produces responses to
* player inputs, manages animation changes... etc.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#include "Player.h"

#include "GameSingletons.h"

Player::Player(const std::vector<Tile>& floorTiles, short& slide, const AudioManager& sound): tiles(floorTiles), currentSlide(slide), rAudio(sound)
{
    // Change the protected values from the Physics class
    Physics::maxSpeed = maxMoveSpeed;
    Physics::maxFallSpeed = 100;
    Physics::gravMultiplier = 1.85f;
    Physics::decelerationRate = 275;
    
    position = {50, 400};
    grounded = true;
    renderer.SetFrameCount(4);
}

void Player::Update(float deltaTime)
{
    controller.Update();
    Pausing();

    if(dead || paused || canFinish) return;

    wc.Update(deltaTime);
    
    DamageTimer(deltaTime);
    SectionDetection();

    // Kill the character if they fall off the level
    if(position.y > GameWindow::GetWindowHeight()) Death();

    // Whenever the float function is called gravity is turned off... 
    if(setFloatTimer)
    {
        floatTimer += deltaTime;

        // This turns it back on when the timer elapses.
        if(floatTimer > floatDuration)
        {
            SetGravity(true);
            setFloatTimer = false;
            floatTimer = 0;
        }
    }
}

// Primarily responsible for handling things that move
void Player::FixedUpdate(float deltaTime)
{
    if(dead || paused || canFinish) return;
    
    wc.FixedUpdate(deltaTime);
    
    // If the jump button is held... gravity is slightly less powerful
    // if the crouch button is being held... gravity is slightly more powerful
    ApplyGravity(true, controller.JumpBtnDown(), controller.CrouchBtnDown());
    
    // Collisions before applying position
    Collisions();

    CoyoteTime(deltaTime);
    
    // Once all the movements have been done... add the velocity to the position
    // and update everything that needs to know.
    position += velocity;
    UpdateRectangle();

    UpdateAnimation();

    // Ran in update to check for the input
    Jump();
    
    Move(deltaTime);
}

void Player::Float()
{
    SetVelocity(0,0);
    SetGravity(false);
    setFloatTimer = true;
}

void Player::Reset()
{
    dead = false;
    respawning = false;
    isDamaged = false;
    dmgTimer = 0;
    health = maxHealth;
    wc.Refill();
    wc.KillBullets();
    
    // To make the player's location more noticeable
    Float();
    
    currentSlide = 0;
    position = {50, 400};
    finished = false;
    canFinish = false;
}

bool Player::GivePowerup()
{
    // If the player's health isn't max .. or the player's ammo isn't full
    const bool canTake = health != maxHealth || !wc.AmmoFull();
    if(!canTake) return canTake;
    
    health++;
    if(health > maxHealth) health = maxHealth;

    rAudio.PlaySound(AudioManager::Esounds::Flowerup);
    
    wc.Refill();

    return canTake;
}

void Player::TakeDamage()
{
    if(isDamaged) return;
    
    isDamaged = true;
    health--;

    rAudio.PlaySound(AudioManager::Esounds::PlayerHit);
    
    if(health < 1) Death();
}

// The player is only responsible for setting the position.
// The renderer is only responsible for setting the size.
// Together, they make the rectangle.
void Player::UpdateRectangle()
{
    const Vector2 playerSize = renderer.GetDrawSize();

    rect.x = position.x;
    rect.y = position.y;
    rect.w = playerSize.x;
    rect.h = playerSize.y;
}

void Player::FinishLevel()
{
    finished = canFinish;
}

void Player::CoyoteTime(float deltaTime)
{
    if(grounded) coyoteTimer = coyoteDuration;
    else coyoteTimer -= deltaTime;
}

void Player::Pausing()
{
    // Can't pause when dead
    if(dead) return;
    
    paused = controller.PauseDown();
}

void Player::Unpause()
{
    paused = false;

    // So that you don't have to toggle the pause button to pause again the (next time)
    controller.ResetPaused();
}

// Called in Update. Used to determine when the player should load into the next section of the level.
// Also moves the player and the active bullets to the start/end of the screen depending on the direction the player is going in.
void Player::SectionDetection()
{
    if(position.x + velocity.x + rect.w > GameWindow::GetWindowWidth())
    {
        // Since the slide is a reference, it updates the Level object's value too. This value is used to set the other objects
        // That need it too.
        currentSlide++;
        position.x = -rect.w/2;

        for (auto& bullet : wc.GetActiveBullets())
        {
            bullet.SetPosition(Vector2(0, bullet.GetPosition().y));
        }
    }
    
    else if(currentSlide > 0 && position.x + velocity.x < -rect.w - 1)
    {
        currentSlide--;

        // Keep the velocity and set the position to the right of the screen (the velocity would be going left if going to the previous slide)
        position.x = GameWindow::GetWindowWidth() - rect.w;

        
        for (auto& bullet : wc.GetActiveBullets())
        {
            bullet.SetPosition(Vector2(GameWindow::GetWindowWidth(), bullet.GetPosition().y));
        }
    }

    // Stop the player from going offscreen if there isn't a slide
    else if(currentSlide == 0 && position.x + velocity.x < 0)
    {
        velocity.x = 0;
        position.x = 0;
    }
}

void Player::Death()
{
    dead = true;
    health = 0;

    // Stop all the other sounds first, then play all of these.
    rAudio.PlaySound(AudioManager::Esounds::PlayerHit, false);
    rAudio.PlaySound(AudioManager::Esounds::ProjImpact);
    rAudio.PlaySound(AudioManager::Esounds::SlimeDeath);
}

void Player::DamageTimer(float deltaTime)
{
    if(!isDamaged) return;

    dmgTimer += deltaTime;

    if(dmgTimer < dmgCooldown) return;

    dmgTimer = 0;
    isDamaged = false;
    renderer.ChangeSpriteSheet(direction == 0? 0 : 1);
}

void Player::Collisions()
{
    // Separating the collision detection into vertical and horizontal to manage the grounded value.
    const Vector2 predictedPosX = position + Vector2(velocity.x, 0);
    const Vector2 predictedPosY = position + Vector2(0, velocity.y);
    const auto predictedRectX = SDL_FRect{ predictedPosX.x, predictedPosX.y, renderer.GetDrawSize().x, renderer.GetDrawSize().y };
    const auto predictedRectY = SDL_FRect{predictedPosY.x, predictedPosY.y, renderer.GetDrawSize().x, renderer.GetDrawSize().y};

    grounded = false;
    for (auto& tile : tiles)
    {
        // Don't collide with anything that isn't visible / in the same slide
        if(tile.GetLevelSlide() != currentSlide) continue;

        // Getting the rect of the tile doesn't work since its position is a reference (?) have to get it's size and position separetly.
        const SDL_FRect tileRect = SDL_FRect{ tile.GetRenderer().GetPosition().x, tile.GetRenderer().GetPosition().y, tile.GetRenderer().GetDrawSize().x, tile.GetRenderer().GetDrawSize().y};
        
        // Separate the axis collisions.
        const bool predictedCollisionX = SDL_HasIntersectionF(&predictedRectX, &tileRect);
        const bool predictedCollisionY = SDL_HasIntersectionF(&predictedRectY, &tileRect);

        // If you collide with an end tile... just end the game.
        if(tile.IsFinishLine() && (predictedCollisionX || predictedCollisionY))
        {
            canFinish = true;
            return;
        }

        // Remove horizontal velocity but keep vertical the same.
        if (predictedCollisionX) velocity = Vector2(0, velocity.y);
        
        if (predictedCollisionY)
        {
            // Remove vertical velocity but keep horizontal the same.
            velocity = Vector2(velocity.x, 0);

            // Prevents grounded being set to true if the collision is above the player.
            grounded = position.y + renderer.GetDrawSize().y < tileRect.y;
        }

    }
    
}

void Player::UpdateAnimation()
{
    const bool moving = abs(velocity.x) > .5f;
    const bool falling = abs(velocity.y) > 2;

    renderer.SetAnimSpeed(moving? runAnimSpeed : idleAnimSpeed);
    
    if(isDamaged)
    {
        if(moving) renderer.ChangeSpriteSheet(dmgRunAnim);
        else renderer.ChangeSpriteSheet(dmgIdleAnim);
    }

    else
    {
        if(moving && !falling) renderer.ChangeSpriteSheet(runAnim);
        else renderer.ChangeSpriteSheet(idleAnim);
    }
}

void Player::Propel(Vector2 dir, float force)
{
    // Since grounded fluctuates too much to use.
    if(GetAirTime() > .025f) AddForce(dir, force, true);
}

void Player::Move(float deltaTime)
{
    // If left dir = -1 ... otherwise ... if right dir = 1 ... otherwise dir = 0
    // Done like this so that direction = 0 whenever there isn't an input (it doesn't remember the last input)
    direction = controller.IsLeft()? -1 : (controller.IsRight()? 1: 0);

    renderer.SetFlip(direction < 0);    
    
    // Adds initial velocity if the player isn't moving to being the acceleration.
    if(direction != 0 && abs(velocity.x) < .01f) velocity.x += direction * .1f;

    // decelerate if there is no input or moving in the opposite direction
    decelerating = direction == 0 || (direction > 0 && velocity.x < -.01f) ^ (direction < 0 && velocity.x > .01f);
    Deceleration(deltaTime);

    // Since the grounded bool will fluctuate (since it's set before this is run)
    const bool falling = GetAirTime() > .03f;

    // Interpolating to the max speed...
    const float percentage = abs(velocity.x) / maxSpeed;

    float acceleration;

    // If you're in the air use a multiplier to make controls more responsive (Get rewarded for being in the air)
    if(!setFloatTimer) acceleration = percentage * (falling? accelerationRate * airControl: accelerationRate);

    // If the float ability is enabled... give more air control
    else acceleration = percentage * airControl * accelerationRate / 2;
    
    velocity.x += direction * acceleration * deltaTime;

    if(velocity.x > maxSpeed) velocity.x = maxSpeed;
    if(velocity.x < -maxSpeed) velocity.x = -maxSpeed;
}

void Player::Deceleration(float deltaTime)
{
    // Don't decelerate if you're in the air or changing directions
    if(!grounded) return;
    
    // if the speed from the previous frame is the same as the speed in this frame... decelerate
    if(decelerating && abs(velocity.x) > .01f)
    {
        const float percentage = velocity.x / drag;
        const float deceleration = decelerationRate * percentage;
        velocity.x -= deceleration * deltaTime;

        if(abs(velocity.x) <= 0) velocity.x = 0;
    }
}

void Player::Jump()
{
    // Allowed to jump if the jump button is pressed or the jump buffer is active
    jumping = controller.JumpBtnDown() || jumpBuffer;

    // Activate the jump buffer if you're in the air for .3 seconds and the jump button is pressed
    if(GetAirTime() > .3f && !grounded && jumping) jumpBuffer = true; 
    
    if (coyoteTimer <= 0) return;

    // Doing jumping in the same way as normal movement to make the jump smoother
    const float forceDifference = position.y / (position.y + jumpHeight);
    const float thrust = forceDifference * jumpForce;

    if(jumping)
    {
        AddForce(0,1, coyoteTimer < coyoteDuration / 4? -thrust * 2: -thrust);
        rAudio.PlaySound(AudioManager::Esounds::Jump);
        coyoteTimer = 0;
    }

    
    // if jump buffer was true... set it to false
    jumpBuffer = jumpBuffer? false: jumpBuffer;
}