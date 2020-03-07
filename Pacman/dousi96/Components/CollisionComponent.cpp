#include "CollisionComponent.h"

CollisionComponent::CollisionComponent()
{
}

CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::Start()
{
}

void CollisionComponent::Update(const float deltaTime)
{
	Vector2f distanceVector;
	for (unsigned int i = 0; i < targets.size(); ++i) 
	{
		if (targets[i] == nullptr) 
		{
			continue;
		}

		distanceVector = this->Owner->Position - targets[i]->Position;
		if (distanceVector.Length() < 0.5f) 
		{
			CollisionEventArgs args;
			args.sender = this->Owner;
			args.hit = targets[i];
			Dispatch(args);
		}
	}
}

void CollisionComponent::AddTarget(GameObject* newTarget)
{
	if (newTarget == nullptr) 
	{
		return;
	}
	targets.push_back(newTarget);
}
