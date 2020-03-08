#include "Component.h"
#include "../GameController.h"

Component::Component()
{
	this->isActive = true;
}

void Component::Register(GameObject* gameObject)
{
	Owner = gameObject;
}

void Component::Update(const float& deltaTime)
{
	if (isActive) 
	{
		_Update(deltaTime);
	}	
}

void Component::Draw() const
{
	if (isActive)
	{
		_Draw();
	}
}

void Component::SetActive(const bool active)
{
	this->isActive = active;
}

bool Component::IsActive() const
{
	return this->isActive;
}

GameObject* Component::GetOwner() const
{
	return this->Owner;
}

