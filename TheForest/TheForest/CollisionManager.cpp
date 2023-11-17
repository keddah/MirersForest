#include "Collider.h"

void CollisionManager::Update(float deltaTime)
{
    for(int i = 0; i < colliders.size(); i++)
    {
        colliders[i]->Debug();
        colliders[i]->SetRectangle(colliders[i]->GetRect());
        
        if(i > 0) colliders[i]->Overlapping(colliders[i - 1]->GetRect());
        else colliders[i]->Overlapping(colliders.back()->GetRect());
    }

    print(colliders[1]->IsOverlapping())
}

void CollisionManager::AddCollider(const Collision& toAdd)
{
    colliders.push_back(toAdd);
}
