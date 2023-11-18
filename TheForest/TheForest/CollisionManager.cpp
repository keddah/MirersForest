#include "Collider.h"

void CollisionManager::Update() const
{
    for(const auto& collider1: colliders)
    {
        for(const auto& collider2: colliders)
        {
            if(collider1 == collider2) continue;

            collider1->Overlapping(*collider2);
        }
    }
        
    // colliders[0]->IsOverlapping();
}


void CollisionManager::Debug() const
{
    for(const auto& collider:colliders) collider->Debug();
}


void CollisionManager::AddCollider(Collision& toAdd)
{
    colliders.push_back(&toAdd);
}
