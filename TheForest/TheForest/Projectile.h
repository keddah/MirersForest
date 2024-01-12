/**************************************************************************************************************
* Projectile - Header
*
* The header file for the Projectile class. Declares the projectile types, creates the renderer for the death vfx and the projectile itself
* as well as stores the file paths for the projectile and impact sprites.  
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

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

	void Update(float deltaTime);
	void FixedUpdate();

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
	
	bool IsDead()
	{ 
		if (dead)
		{
			// Free up the memory the renderer was using when the projectile dies.
			renderer.DestroyAllTextures(); 
			impactVfx.DestroyAllTextures();
		}
		return dead; 
	}

	bool IsDying() const { return dying; }
	bool IsSpecial() const { return special; }
	
	void Kill() { dying = true;}
	void Explode();
	void Beam(float deltaTime, Vector2 mousePos);
	
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
	

	// In seconds
	const short lifeSpan = 5;
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
	
	// Impacts
	std::string impactPath;
	const std::vector<std::string> impactPaths
	{
		"Sprites/Projectiles/seedImpactSheet.png",
		"Sprites/Projectiles/petalImpactSheet.png",
		"Sprites/Projectiles/sunBeamSheet.png",
		"Sprites/Projectiles/seedExplosionSheet2.png"
	};
	
	float impactOffset;
	SpriteRenderer renderer = SpriteRenderer(typePaths, position, false);
	SpriteRenderer impactVfx = SpriteRenderer(impactPaths, position, true, false);

	EWeaponTypes type;
	
	// Is the alternative weapon type (each weapon type has 2 abilities)
	bool special;
	
	float flipTimer;
	const float beamFlipDelay = .7f; 
	
	float shootDelay = .8f;
	short ammoCost = 1;

	float force = 8;

	float renderRot;
	Vector2 renderPivot;
	

	Vector2 repulsion;
};
