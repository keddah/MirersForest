#include "Collider.h"

void CollisionManager::Update() const
{
    for(const auto& collider: colliders) collider->Update();
}


void CollisionManager::Debug() const
{
    for(const auto& collider:colliders) collider->Debug();
}


void CollisionManager::AddCollider(Collision& toAdd)
{
    colliders.push_back(&toAdd);
}
