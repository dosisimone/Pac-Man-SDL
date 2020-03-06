#include "Component.h"

void Component::Register(GameObject* gameObject)
{
	Owner = gameObject;
}

