#include "WeaponController.h"

WeaponController::WeaponController(Player* plyr)
{
    player = plyr;
}

WeaponController::~WeaponController()
{
    delete player;  
}

void WeaponController::Update(double deltaTime)
{
    
}
