#include "CollisionComponent.h"
#include "../../GameController.h"

CollisionComponent::CollisionComponent()
{
}

CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::AddTarget(GameObject* newTarget)
{
	if (newTarget == nullptr) 
	{
		return;
	}
	targets.push_back(newTarget);
}

void CollisionComponent::_Update(const float& deltaTime)
{
	Vector2f distanceVector;
	for (unsigned int i = 0; i < targets.size(); ++i)
	{
		if (targets[i] == nullptr)
		{
			continue;
		}

		distanceVector = GetOwner()->Position - targets[i]->Position;
		if (distanceVector.Length() < 0.1f)
		{
			CollisionStatus status = CollisionStatus::Enter;
			if (collisionsStatus.count(targets[i]) == 0)
			{
				collisionsStatus.insert({ targets[i], status });
			}
			else
			{
				status = CollisionStatus::Stay;
				collisionsStatus[targets[i]] = status;
			}

			CollisionEventArgs args;
			args.sender = GetOwner();
			args.hit = targets[i];
			args.status = status;
			Invoke(args);
		}
		else
		{
			if (collisionsStatus.count(targets[i]) > 0)
			{
				CollisionEventArgs args;
				args.sender = GetOwner();
				args.hit = targets[i];
				args.status = CollisionStatus::Exit;
				Invoke(args);
				collisionsStatus.erase(targets[i]);
			}
		}
	}
}
