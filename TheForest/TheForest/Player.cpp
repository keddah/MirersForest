#include "Player.h"
#include <math.h>

Player::Player(std::vector<Tile>& floorRef): floor(floorRef)
{
    maxSpeed = 10;

    maxFallSpeed = 50;
}

void Player::Update(float deltaTime)
{
    controller.Update();
    
    // Reset velocity at the start of each frame so that it doesn't infinitely increase.
    //velocity.x = velocity.x > maxSpeed ? maxSpeed: velocity.x;
    //velocity.y = velocity.y > maxSpeed ? maxSpeed: velocity.y;

    // If the jump button is held... gravity is slightly less powerful
    // if the crouch button is being held... gravity is slightly dmore powerful
    ApplyGravity(controller.GetMoveInputs()[0], controller.GetMoveInputs()[1]);
   
    // Move has to be called first so that collisions can negate its newly added velocity.
    // Move(deltaTime);
    Collisions();
    
    // Once all the movements have been done... add the velocity to the position
    // and update everything that needs to know.
    pos += velocity;
    UpdateRectangle();
}

void Player::FixedUpdate(float deltaTime)
{
    Move(deltaTime);
}

void Player::Init()
{
    if(initialised) return;

    renderer.SetIsAnimated();
    
    initialised = true;
}

// The player is only responsible for setting the position.
// The renderer is only responsible for setting the size.
// Together, they make the rectangle.
void Player::UpdateRectangle()
{
    const Vector2 playerSize = renderer.GetDrawSize();

    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = playerSize.x;
    rect.h = playerSize.y;
}

void Player::Collisions()
{
    const Vector2 predictedPosX = pos + Vector2(velocity.x, 0);
    const Vector2 predictedPosY = pos + Vector2(0, velocity.y);
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

    const bool left = controller.GetMoveInputs()[2];
    const bool right = controller.GetMoveInputs()[3];

    // If left dir = -1 ... otherwise ... if right dir = 1 ... otherwise dir = 0
    direction = left? -1 : (right? 1: 0);

    // Adds initial velocity if the player isn't moving to being the acceleration.
    if(direction != 0 && abs(velocity.x) < .01f) velocity.x += direction * .1f;

    decelerating = direction == 0;
    Deceleration(direction != 0, deltaTime);
    
    const float percentage = abs(velocity.x) / maxSpeed;
    const float acceleration = percentage * accelerationRate;
    
    if(!decelerating) velocity.x += direction * acceleration * deltaTime;
   
    
    if(velocity.x > maxSpeed) velocity.x = maxSpeed;
    if(velocity.x < -maxSpeed) velocity.x = -maxSpeed;
}

void Player::Deceleration(bool turning, float deltaTime)
{
    if(turning) return;
    // if the speed from the previous frame is the same as the speed in this frame... decelerate
    if(decelerating && abs(velocity.x) > .01)
    {
        const float percentage = abs(velocity.x) / slowSpeed;
        const float deceleration = turning? decelerationRate * 10: decelerationRate * percentage;
        velocity.x -= abs(deceleration) * deltaTime;

        if(abs(velocity.x) <= 0) velocity.x = 0;
        print("deceleratingsdgfisf")
    }
}

void Player::Jump()
{
    // Allowed to jump if the jump button is pressed or the jump buffer is active
    jumping = controller.GetMoveInputs()[0] || jumpBuffer;

    // Activate the jump buffer if you're in the air for .3 seconds and the jump button is pressed
    if(GetAirTime() > .3f && !grounded && jumping) jumpBuffer = true; 
    
    if (!grounded) return;

    const float forceDifference = pos.y / (pos.y + jumpHeight);
    const float thrust = forceDifference * jumpForce;

    if(jumping) AddForce(0,1, -thrust);
    
    // if jump buffer was true... set it to false
    jumpBuffer = jumpBuffer? false: jumpBuffer;
}

void Player::Crouch()
{
}

