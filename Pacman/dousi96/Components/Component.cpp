#include "Component.h"

void Component::Register(GameObject* gameObject)
{
	if (gameObject == nullptr) 
	{
		return;
	}
	Owner = gameObject;
}
