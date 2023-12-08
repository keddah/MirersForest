#pragma once

#include <tuple>

#include "Physics.h"
#include "Renderers.h"

class Projectile : public Physics
{
public:
	enum class EWeaponTypes
	{
		Seed,
		Petal,
		Sun,
		Thorn,
	};
	
	Projectile(const std::tuple<EWeaponTypes, float, float, short, float, float>& weapon, Vector2 pos, float angle, Vector2 plyrVelocity, bool isSpecial);
	// ~Projectile() { delete renderer; }
	
	virtual void Update();
	virtual void Draw();


	Projectile& operator=(const Projectile& other)
	{
		    lifeTimer = other.lifeTimer;
		    dead = other.dead;
		
		    typePath = other.typePath;
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
		dead = lifeTimer > lifeSpan;
	}
	
	bool IsDead() const { return dead; }
	
	const Vector2& GetRepulsion() const { return repulsion; }
	
private:
	const float lifeSpan = 8;
	float lifeTimer;
	bool dead = false;
	
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
