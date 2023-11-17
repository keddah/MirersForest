#include "Collider.h"

void CollisionManager::Update() const
{
    for(int i = 0; i < colliders.size(); i++)
    {
        for(int j = 0; j < colliders.size(); j++)
        {
            if(i == j) continue;

            colliders[i]->Overlapping(colliders[j]->GetRect());
        }
    }
    
        print(": " << colliders[0]->IsOverlapping())
}


void CollisionManager::Debug() const
{
    for(const auto& collider:colliders) collider->Debug();
}


void CollisionManager::AddCollider(Collision& toAdd)
{
    colliders.push_back(&toAdd);
}
