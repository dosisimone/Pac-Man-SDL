#include "Components/Component.h"
#include "GameObject.h"

GameObject::GameObject(const Vector2f& position)
{
	this->Tag = GameObjectTag::Default;
	this->Position = position;
	this->isActive = true;
}

GameObject::~GameObject()
{
	for (Component* component : components) 
	{
		delete component;
	}
}

void GameObject::Draw() const
{
	if (!isActive)
	{
		return;
	}
	_DrawComponents();
}

void GameObject::Update(const float deltaTime)
{
	if (!isActive) 
	{
		return;
	}
	_StartComponents();
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

void GameObject::_StartComponents()
{
	for (Component* componentToStart : componentsToStart)
	{
		componentToStart->Start();
	}
	componentsToStart.clear();
}

void GameObject::_DrawComponents() const
{
	for (Component* component : components)
	{
		component->Draw();
	}
}

void GameObject::_UpdateComponents(const float deltaTime)
{
	for (Component* component : components) 
	{
		component->Update(deltaTime);
	}
}
