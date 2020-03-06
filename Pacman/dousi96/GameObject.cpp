#include "Components/Component.h"
#include "GameObject.h"

GameObject::GameObject(const Vector2f& position)
{
	this->Position = position;
	this->isActive = true;
}

GameObject::~GameObject()
{
	for (unsigned int i = 0; i < components.size(); ++i) 
	{
		delete components[i];
	}
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

void GameObject::RemoveComponent(Component* component)
{
	for (unsigned int i = 0; i < components.size(); ++i)
	{
		if (component == components[i]) 
		{
			components.erase(components.begin() + i);
			delete component;
			component = nullptr;
			return;
		}
	}	
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
