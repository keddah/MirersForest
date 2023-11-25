#include "Collider.h"

void CollisionManager::Update()
{
    for(auto& collider: colliders) collider.Update();
}


void CollisionManager::Debug()
{
    for(auto& collider:colliders) collider.Debug();
}


void CollisionManager::AddCollider(const Collision& toAdd)
{
    colliders.push_back(toAdd);
}
