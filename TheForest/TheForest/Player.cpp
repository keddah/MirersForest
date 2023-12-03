#include "Player.h"

#include "CustomTimer.h"

Player::Player(std::vector<Tile>& floorRef): floor(floorRef)
{
    maxSpeed = 12.5f;

    maxFallSpeed = 50;
    renderer.SetIsAnimated();

}

void Player::Update(float deltaTime)
{
    controller.Update();

    // If the jump button is held... gravity is slightly less powerful
    // if the crouch button is being held... gravity is slightly more powerful
    ApplyGravity(controller.JumpBtnDown(), controller.CrouchBtnDown());
   
    // Move has to be called first so that collisions can negate its newly added velocity.
    // Move(deltaTime);
    Collisions();
    
    // Once all the movements have been done... add the velocity to the position
    // and update everything that needs to know.
    _position += velocity;
    UpdateRectangle();

    Shooting();
}

void Player::FixedUpdate(float deltaTime)
{
    Move(deltaTime);
}

void Player::UpdateBullets()
{
    for(auto& bullet : activeBullets) bullet.Update();
}

void Player::DrawBullets()
{
    for(auto& bullet : activeBullets) bullet.Draw();
}

// The player is only responsible for setting the position.
// The renderer is only responsible for setting the size.
// Together, they make the rectangle.
void Player::UpdateRectangle()
{
    const Vector2 playerSize = renderer.GetDrawSize();

    rect.x = _position.x;
    rect.y = _position.y;
    rect.w = playerSize.x;
    rect.h = playerSize.y;
}

void Player::Collisions()
{
    const Vector2 predictedPosX = _position + Vector2(velocity.x, 0);
    const Vector2 predictedPosY = _position + Vector2(0, velocity.y);
    const auto predictedRectX = SDL_FRect{ predictedPosX.x, predictedPosX.y, renderer.GetDrawSize().x, renderer.GetDrawSize().y };
    const auto predictedRectY = SDL_FRect{predictedPosY.x, predictedPosY.y, renderer.GetDrawSize().x, renderer.GetDrawSize().y};

    grounded = false;
    for (auto& tile : floor)
    {
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

void Player::Move(float deltaTime)
{
    Jump();


    // If left dir = -1 ... otherwise ... if right dir = 1 ... otherwise dir = 0
    direction = controller.IsLeft()? -1 : (controller.IsRight()? 1: 0);

    // Adds initial velocity if the player isn't moving to being the acceleration.
    if(direction != 0 && abs(velocity.x) < .01f) velocity.x += direction * .1f;

    decelerating = direction == 0;
    Deceleration(direction != 0, deltaTime);

    // Since the grounded bool will fluctuate (since it's set before this is run)
    const bool falling = GetAirTime() > .1f;

    // Interpolating to the max speed...
    const float percentage = abs(velocity.x) / maxSpeed;

    // If you're in the air use a multiplier to make controls more responsive (Get rewarded for being in the air)
    const float acceleration = percentage * (falling? accelerationRate * airControl: accelerationRate);
    
    if(!decelerating) velocity.x += direction * acceleration * deltaTime;
   
    
    if(velocity.x > maxSpeed) velocity.x = maxSpeed;
    if(velocity.x < -maxSpeed) velocity.x = -maxSpeed;
}

void Player::Deceleration(bool turning, float deltaTime)
{
    // Don't decelerate if you're in the air or changing directions
    if(turning || !grounded) return;
    
    // if the speed from the previous frame is the same as the speed in this frame... decelerate
    if(decelerating && abs(velocity.x) > .01)
    {
        const float percentage = velocity.x / drag;
        const float deceleration = turning? decelerationRate * 10: decelerationRate * percentage;
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
    
    if (!grounded) return;

    const float forceDifference = _position.y / (_position.y + jumpHeight);
    const float thrust = forceDifference * jumpForce;

    if(jumping) AddForce(0,1, -thrust);
    
    // if jump buffer was true... set it to false
    jumpBuffer = jumpBuffer? false: jumpBuffer;
}

void Player::Shooting()
{
    // Update the projectile spawn position; 
    projectileSpawn = Vector2(_position.x + rect.w/2, _position.y + rect.h/2) + Vector2(direction * projSpawnOffset, 0);
    
    if(!canShoot)
    {
        shootTimer += Time::GetDeltaTime();
        if(shootTimer > activeBullets.back().GetShootDelay())
        {
            shootTimer = 0;
            canShoot = true;
        }
        
        return;
    }


    if(!(controller.IsLMB() || controller.IsRMB())) return;
    
    Projectile newBullet = Projectile(selectedWeapon, projectileSpawn, controller.IsRMB());
    activeBullets.emplace_back(newBullet);
    canShoot = false;
}
