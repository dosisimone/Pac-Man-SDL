#include "Components/Component.h"
#include "GameObject.h"

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
	unsigned int indexToErase = -1;
	for (unsigned int i = 0; i < components.size(); ++i)
	{
		if (component == components[i]) 
		{
			indexToErase = i;
			break;
		}
	}
	if (indexToErase > -1)
	{
		components.erase(components.begin() + indexToErase);
	}
	delete component;
}

GameController* GameObject::GetController() const
{
	return controller;
}

void GameObject::SetActive(const bool active)
{
	isActive = active;
}

GameObject* GameObject::CreateGameObject(GameController* controller, const Vector2f& position)
{
	GameObject* newGameObject = new GameObject(position);
	newGameObject->_Register(controller);	
	return newGameObject;
}

GameObject::GameObject(const Vector2f& position)
{
	this->controller = nullptr;
	this->Position = position;
	this->isActive = true;
}

void GameObject::_Register(GameController* controller)
{
	this->controller = controller;
}

void GameObject::_UpdateComponents(const float deltaTime)
{
	for (Component* component : components) 
	{
		component->Update(deltaTime);
	}
}
