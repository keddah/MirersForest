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
	void FixedUpdate(float deltaTime);

	void Draw();
	void DeathAnimation(bool referenced = true);

	const SpriteRenderer& GetVFX() const { return impactVfx; }
		
	void SetPosition(Vector2 pos) {position = pos;}
	
	Projectile& operator=(const Projectile& other)
	{
		    lifeTimer = other.lifeTimer;
		    dead = other.dead;
		
		    type = other.type;
		    special = other.special;
		    shootDelay = other.shootDelay;
		    ammoCost = other.ammoCost;
		    force = other.force;
		    renderRot = other.renderRot;
		    renderPivot = other.renderPivot;
		    repulsion = other.repulsion;
		    return *this;
	}
	
	void Expire(const float time)
	{
		lifeTimer += time;
		if (lifeTimer > lifeSpan) dead = true;
	}
	
	bool IsDead() const { return dead; }
	bool IsDying() const { return dying; }
	bool IsSpecial() const { return special; }
	
	void Kill() { dying = true;}
	void Explode();
	void Beam(float deltaTime, Vector2 mousePos);
	// bool IsPulling() const { return pulling; }
	// const Vector2& GetPullPos() const { return pullPos; }
	
	const Vector2& GetRepulsion() const { return repulsion; }

	const SpriteRenderer& GetRenderer() const { return renderer; }

	const Vector2& GetPosition() const { return position; }
	const SDL_FRect& GetRect() const { return renderer.GetRect(); }
	EWeaponTypes GetType() const { return type; }

	bool sfxPlaying;
	
private:
	const std::vector<Tile>& tiles;

	void FaceVelocity();
	void UpdateRect();
	
	void Collisions();
	

	void Pull(Vector2  pullFrom);
	
	const float lifeSpan = 8;
	float lifeTimer;
	bool dead = false;
	bool dying = false;

	SDL_FRect rect;
	
	const std::vector<std::string> typePaths
	{
		"Sprites/Projectiles/Projectile_seed.png",
		"Sprites/Projectiles/Projectile_seedBig.png",
		"Sprites/Projectiles/Projectile_petal.png",
		"Sprites/Projectiles/Projectile_sun.png",
	};
	
	// const std::string seedPath {"Sprites/Projectiles/Projectile_seed.png"};
	// const std::string bigSeedPath {"Sprites/Projectiles/Projectile_seedBig.png"};
	// const std::string petalPath {"Sprites/Projectiles/Projectile_petal.png"};
	// const std::string sunPath {"Sprites/Projectiles/Projectile_sun.png"};
	// const std::string thornPath {"Sprites/Projectiles/Projectile_thorn.png"};

	// Impacts
	std::string impactPath;
	const std::vector<std::string> impactPaths
	{
		"Sprites/Projectiles/seedImpactSheet.png",
		"Sprites/Projectiles/petalImpactSheet.png",
		"Sprites/Projectiles/sunBeamSheet.png",
		"Sprites/Projectiles/seedExplosionSheet2.png"
	};
	// const std::string seedImpact {"Sprites/Projectiles/Projectile_thorn.png"};
	// const std::string petalImpact {"Sprites/Projectiles/petalImpactSheet.png"};
	// const std::string sunImpact {"Sprites/Projectiles/Projectile_thorn.png"};
	// const std::string explosionPath {"Sprites/Projectiles/seedExplosionSheet.png"};
	
	float impactOffset;
	// SpriteRenderer* renderer;// = SpriteRenderer(position, {20,20});
	SpriteRenderer renderer = SpriteRenderer(typePaths, position, false);
	SpriteRenderer impactVfx = SpriteRenderer(impactPaths, position, true, false);

	
	// Using a vector so that it can be initialised in a switch (without using a pointer)	
	// std::vector<SpriteRenderer> impactVfx = std::vector<SpriteRenderer>();
	
	EWeaponTypes type;
	
	// Is the alternative weapon type (each weapon has 2 types)
	bool special;
	// bool pulling;
	// Vector2  pullPos;
	float flipTimer;
	const float beamFlipDelay = .7f; 
	
	float shootDelay = .8f;
	short ammoCost = 1;
	float rechargeDelay;

	float force = 8;

	float renderRot;
	Vector2 renderPivot;
	
	const short blastRadius = 15;

	Vector2 repulsion;
};
