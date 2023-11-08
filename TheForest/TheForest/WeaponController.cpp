#include "Controllers.h"

WeaponController::WeaponController(PlayerController& ctrl, Vector2& plyrPos) : controller(ctrl), playerPosition(plyrPos)
{
}

WeaponController::~WeaponController()
{
}

void WeaponController::Update(float deltaTime)
{
    static const Vector2 offset = Vector2(2,2);
    spawnPos = playerPosition + offset;

    primaryShot = controller.IsLMB();
    secondaryShot = controller.IsRMB();
}
