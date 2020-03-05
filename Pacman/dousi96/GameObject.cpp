#include "Components/Component.h"
#include "GameObject.h"

GameObject::GameObject() : GameObject(Vector2f::ZERO)
{
}

GameObject::GameObject(const Vector2f& position) : isActive(true), Position(position)
{
}

void GameObject::Draw() const
{
	if (!isActive)
	{
		return;
	}

	for (Component* component : components)
	{
		component->Draw();
	}
}

void GameObject::Update(const float deltaTime)
{
	if (!isActive) 
	{
		return;
	}

	_UpdateComponents(deltaTime);
}

Component* GameObject::GetComponentByType(const ComponentType type)
{
	for (Component* component : components)
	{
		if (component->GetType() == type) 
		{
			return component;
		}
	}
	return nullptr;
}

void GameObject::RemoveComponent(Component* component)
{
	components.remove(component);
	delete component;
}

void GameObject::SetActive(const bool active)
{
	isActive = active;
}

void GameObject::_UpdateComponents(const float deltaTime)
{
	for (Component* component : components) 
	{
		component->Update(deltaTime);
	}
}
