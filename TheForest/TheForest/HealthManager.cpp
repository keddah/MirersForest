#include "HealthManager.h"
//#include "GameCharacter.h"


HealthManager::HealthManager()
{
}

//HealthManager::HealthManager(Character _owner)
//{
//	Owner = _owner;
//}

HealthManager::~HealthManager()
{
}

void HealthManager::TakeDamage(float damageIntensity)
{
	if (damageIntensity >= damageResistance)
		currentLives--;

	else if (damageIntensity == damageResistance / 2) currentLives -= .5;
}

void HealthManager::GainHealth()
{
	currentLives++;
}
