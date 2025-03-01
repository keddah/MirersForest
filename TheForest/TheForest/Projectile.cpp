/**************************************************************************************************************
* Projectile - Code
*
* The code file for the Projectile class. Responsible for giving the correct properties to the projectile that is spawned by the player.
* On creation, the object will be able to become any of the projectile types but the parameters given in its constructor determine
* what type of projectile it is.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

#include "Projectile.h"

#include <random>

#include "Player.h"

Projectile::Projectile(const std::tuple<EWeaponTypes, float, float, short, float, float>& weapon,
	const Vector2 pos, const float angle, const Vector2 plyrVelocity, const bool isSpecial, const std::vector<Tile>& floorRef) : tiles(floorRef)
{
	position = pos;

	type = std::get<0>(weapon);
	force = std::get<1>(weapon);
	gravMultiplier = std::get<4>(weapon);
	decelerationRate = 10;

	special = isSpecial;
	
	maxSpeed = 1000;
	maxFallSpeed = 20;

	// Add the player's velocity onto the launch force.
	SetVelocity(plyrVelocity);
	if(!(type == EWeaponTypes::Sun && special)) AddForce(Vector2(cos(angle), sin(angle)), force);

	// The repulsion is just the opposite direction the projectile is going
	repulsion = velocity * -1;

	switch (type)
	{
		case EWeaponTypes::Seed:
			renderer.ChangeSpriteSheet(special? 1 : 0);

			impactVfx.ChangeSpriteSheet(special? 3 : 0);
			impactVfx.SetAnimSpeed(.025f);
			impactVfx.SetFrameCount(special? 11 : 12);
			
			// impactVfx = new SpriteRenderer(impactPath, position, true, false);
			impactOffset = special? -50 : -30;
			break;
				
		case EWeaponTypes::Petal:
			renderer.ChangeSpriteSheet(2);
			
			impactVfx.ChangeSpriteSheet(1);
			impactVfx.SetAnimSpeed(.026f);
			impactVfx.SetFrameCount(12);

			impactOffset = -30;
			break;
			
		case EWeaponTypes::Sun:
			renderer.ChangeSpriteSheet(3);

			renderPivot = {0, renderer.GetRect().y + renderer.GetRect().h / 2};
			
			impactVfx.ChangeSpriteSheet(2);
			impactVfx.SetAnimSpeed(.03f);
			impactVfx.SetFrameCount(11);
			impactOffset = 40;
			break;
				
		// case EWeaponTypes::Thorn:
		// 	typePath = thornPath;
		// 	break;
	}

	if(type == EWeaponTypes::Sun && special)
	{
		SetVelocity();

		// Make the projectile move upwards
		AddForce(Vector2(0, -1), force * 1.75f);
		renderer.SetDrawSize({renderer.GetDrawSize().x * 3, renderer.GetDrawSize().y * 7.5f});
	}

	FaceVelocity();
}

void Projectile::Update(float deltaTime)
{
	if(dying) return;

	// Always face velocity
	FaceVelocity();
	
	// Collisions before applying position
	Collisions();

	position += velocity;
	UpdateRect();
}

void Projectile::FixedUpdate()
{
	if(dying) return;

	ApplyGravity();
}

void Projectile::Draw()
{
	if(dying) return;

	renderer.SetPosition(position);
	
	renderer.Draw(false);
}

void Projectile::DeathAnimation(bool referenced)
{
	if(!dying) return;

	const Vector2 fxPos = {(position.x + renderer.GetDrawSize().x / 2) - impactVfx.GetDrawSize().x / 2, position.y + impactOffset };
	impactVfx.SetPosition(fxPos);
	impactVfx.PlayAnimation(referenced);

	if(!impactVfx.IsAnimating()) dead = true;
}

void Projectile::FaceVelocity()
{
	// Rotate towards the direction it's going in.
	const Vector2 posVel = position + velocity;
	const Vector2 difference = posVel - position;
	renderRot = (atan2(difference.y, difference.x)) * 180 / std::_Pi;
	renderer.SetRenderAngle(renderRot);
}

void Projectile::UpdateRect()
{
	const Vector2 size = renderer.GetDrawSize();

	rect.x = position.x;
	rect.y = position.y;
	rect.w = size.x;
	rect.h = size.y;
}

void Projectile::Collisions()
{
	bool collision = false;
	for (auto& tile : tiles)
	{
		// Getting the rect of the tile doesn't work since its position is a reference (?) have to get it's size and position separately.
		const auto tileRect = tile.GetRect();

		if(SDL_HasIntersectionF(&tileRect, &rect)) collision = true;
	}

	switch (type)
	{
		case EWeaponTypes::Seed:
			if(collision) Explode();
			if(!special) dying = collision;
			break;
			
		case EWeaponTypes::Petal:
			dying = collision; 
			break;
			
		case EWeaponTypes::Sun:
			// If there's a collision and the beam is on its descent
			if(special && collision && flipTimer > beamFlipDelay)
			{
				dying = true;
				velocity = {};
			}
			break;

		// Getting rid of Thorn since SDL_Rects can't be rotated 
		// case EWeaponTypes::Thorn:
		// 	if(collision) Pull({GetRect().x + GetRect().w, GetRect().y + GetRect().h});
		// 	break;
		}
}

void Projectile::Explode()
{
	if(!special) return;

	dying = true;	
}

void Projectile::Beam(float deltaTime, Vector2 mousePos)
{
	if(!(special && type == EWeaponTypes::Sun)) return;

	flipTimer += deltaTime;
	if(flipTimer < beamFlipDelay) return;

	// Reset the velocity every frame so that it's not too fast
	SetVelocity();

	// Follow the mouse position
	const Vector2 difference = mousePos - Vector2(position.x + renderer.GetDrawSize().x / 2, position.y + renderer.GetDrawSize().y / 2);
	const float rot = atan2(difference.y, difference.x);

	// Allow the projectile to move faster
	maxFallSpeed = 1000;
	drag = 6;

	// Changin this also affects the range (falling faster means less time to change direction)
	gravMultiplier = 3.25f;

	AddForce(Vector2(cos(rot), sin(rot)), force);

}
