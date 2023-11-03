#include "Player.h"

void Player::Update()
{
	rect.x = moveController.position.x;
	rect.y = moveController.position.y;
}
