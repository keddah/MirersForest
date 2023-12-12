#include "Projectile.h"

#include "Player.h"

Projectile::Projectile(const std::tuple<EWeaponTypes, float, float, short, float, float>& weapon,
	const Vector2 pos, const float angle, const Vector2 plyrVelocity, const bool isSpecial, const std::vector<Tile>& floorRef) : tiles(floorRef)
{
	position = pos;

	type = std::get<0>(weapon);
	force = std::get<1>(weapon);
	gravityMultiplier = std::get<4>(weapon);
	decelerationRate = 10;

	special = isSpecial;
	
	maxSpeed = 1000;
	maxFallSpeed = 20;

	// Add the player's velocity onto the launch force.
	SetVelocity(plyrVelocity);
	if(!(type == EWeaponTypes::Sun && special)) AddForce(Vector2(cos(angle), sin(angle)), force);

	// The repulsion is just the opposite direction the projectile is going
	repulsion = velocity * -1;
	

	switch (std::get<0>(weapon))
	{
		case EWeaponTypes::Seed:
			typePath = special? bigSeedPath : seedPath; 
			break;
			
		case EWeaponTypes::Petal:
			typePath = petalPath; 
			break;
		
		case EWeaponTypes::Sun:
			typePath = sunPath;
			break;
			
		// case EWeaponTypes::Thorn:
		// 	typePath = thornPath;
		// 	lifeSpan = 2.5f; 
		// 	break;
	}

	renderer = new SpriteRenderer(typePath, position);
	if(typePath == thornPath || typePath == sunPath) renderPivot = {0, renderer->GetRect().y + renderer->GetRect().h / 2};

	if(type == EWeaponTypes::Sun && special)
	{
		SetVelocity();
		AddForce(Vector2(0, -1), force);
		renderer->SetDrawSize({renderer->GetDrawSize().x * 3, renderer->GetDrawSize().y * 7.5f});
	}

	FaceVelocity();
}

void Projectile::Update(float deltaTime)
{
	if(dead) return;

	// When using the thorn weapon... it stretches in order to move... (need to get the previous size before deleting)
	const Vector2 drawSize = {renderer->GetRect().w, renderer->GetRect().h};
	
	// The renderer's position reference doesn't work correctly.
	// Makes a new renderer before a position update....
	delete renderer;

	// The renderer doesn't work when it's made in the constructor
	renderer = new SpriteRenderer(typePath, position);
	renderer->SetRenderAngle(renderRot);

	// Since the sun's special scales the sprite
	if(type == EWeaponTypes::Sun)
	{
		renderer->SetDrawSize({drawSize.x, drawSize.y});
		Beam(deltaTime);
	}

	currentGravity = Gravity * gravityMultiplier;
	ApplyGravity();

	FaceVelocity();
	
	// Collisions before applying position
	Collisions();

	position += velocity;
	UpdateRect();
}

void Projectile::Draw() const
{
	if(dead) return;

	renderer->Draw(false);
}

void Projectile::FaceVelocity()
{
	// Rotate towards the direction it's going in.
	const Vector2 posVel = position + velocity;
	const Vector2 difference = posVel - position;
	renderRot = (atan2(difference.y, difference.x)) * 180 / std::_Pi;
	renderer->SetRenderAngle(renderRot);
}

void Projectile::UpdateRect()
{
	const Vector2 size = renderer->GetDrawSize();

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
		const SDL_FRect tileRect = SDL_FRect{ tile.GetRenderer().GetPosition().x, tile.GetRenderer().GetPosition().y, tile.GetRenderer().GetDrawSize().x, tile.GetRenderer().GetDrawSize().y};

		if(SDL_HasIntersectionF(&tileRect, &rect))
		{
			collision = true;
		}
		
	}

	switch (type)
	{
		case EWeaponTypes::Seed:
			if(collision) Explode();
			if(!special) dead = collision;
			break;
			
		case EWeaponTypes::Petal:
			dead = collision;
			break;
			
		case EWeaponTypes::Sun:
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
	
	dead = true;
}

void Projectile::Beam(float deltaTime)
{
	if(!special) return;

	flipTimer += deltaTime;

	if(flipTimer < .75f) return;

	maxFallSpeed = 300;
	SetVelocity();

	// Turn on gravity too
	gravityMultiplier = 1.25f;
	AddForce(0, 1, force);
}

void Projectile::Pull(Vector2 pullFrom)
{
	pulling = true;
	pullPos = pullFrom;
}
