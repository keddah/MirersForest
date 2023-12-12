#pragma once

#include <tuple>

#include "Physics.h"
#include "Renderers.h"
#include "Tile.h"

class Projectile : public Physics
{
public:
	enum class EWeaponTypes
	{
		Seed,
		Petal,
		Sun
		// Getting rid of Thorn since SDL_Rects can't be rotated 
		//Thorn,
	};
	
	Projectile(const std::tuple<EWeaponTypes, float, float, short, float, float>& weapon, Vector2 pos, float angle, Vector2 plyrVelocity, bool isSpecial, const std::vector<Tile>& floorRef);
	~Projectile() = default;
	
	void Update(float deltaTime);
	void Draw() const;

	void SetPosition(Vector2 pos) {position = pos;}
	
	Projectile& operator=(const Projectile& other)
	{
		    lifeTimer = other.lifeTimer;
		    dead = other.dead;
		
		    type = other.type;
		    special = other.special;
		    delay = other.delay;
		    ammoCost = other.ammoCost;
		    force = other.force;
		    renderRot = other.renderRot;
		    renderPivot = other.renderPivot;
		    repulsion = other.repulsion;
		    return *this;
	}
	
	void Expire(float time)
	{
		lifeTimer += time;
		if (lifeTimer > lifeSpan) dead = true;
	}
	
	bool IsDead() const { return dead; }
	void Kill() { dead = true;}

	bool IsPulling() const { return pulling; }
	const Vector2& GetPullPos() const { return pullPos; }
	
	const Vector2& GetRepulsion() const { return repulsion; }

	const SpriteRenderer* GetRenderer() const { return renderer; }

	const Vector2& GetPosition() const { return position; }
	const SDL_FRect& GetRect() const { return renderer->GetRect(); }
	EWeaponTypes GetType() const { return type; }
	
private:
	const std::vector<Tile>& tiles;

	void FaceVelocity();
	void UpdateRect();
	
	void Collisions();
	
	void Explode();
	void Beam(float deltaTime);

	void Pull(Vector2  pullFrom);
	
	const float lifeSpan = 8;
	float lifeTimer;
	bool dead = false;

	SDL_FRect rect;
	
	std::string typePath;
	const std::string seedPath {"Sprites/Projectiles/Projectile_seed.png"};
	const std::string bigSeedPath {"Sprites/Projectiles/Projectile_seedBig.png"};
	const std::string petalPath {"Sprites/Projectiles/Projectile_petal.png"};
	const std::string sunPath {"Sprites/Projectiles/Projectile_sun.png"};
	const std::string thornPath {"Sprites/Projectiles/Projectile_thorn.png"};
	SpriteRenderer* renderer;// = SpriteRenderer(position, {20,20});

	EWeaponTypes type;
	
	// Is the alternative weapon type (each weapon has 2 types)
	bool special;
	bool pulling;
	Vector2  pullPos;
	float flipTimer;
	
	float delay = .8f;
	short ammoCost = 1;
	float rechargeDelay;

	float force = 8;

	float renderRot;
	Vector2 renderPivot;
	
	float gravityMultiplier = 1;

	const short blastRadius = 15;

	Vector2 repulsion;
};
