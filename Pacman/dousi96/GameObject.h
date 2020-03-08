#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "../Vector2f.h"

class Component;
class RendererComponent;
class GameController;

enum class GameObjectTag : short
{
	Player,
	Ghost,
	BigDot,
	Dot, 
	Background,
	Teleport,
	UI,
	Logic
};

class GameObject
{
public:	
	Vector2f Position;
	GameObjectTag Tag;

private:	
	bool isActive = false;
	std::vector<Component*> components;	

public:
	GameObject(const Vector2f& position);
	~GameObject();	
	void Draw() const;
	void Update(const float deltaTime);

	template<class T = Component>
	T* AddComponent() 
	{
		T* component = new T();
		component->Register(this);
		components.push_back(component);
		component->Start();
		return component;
	}
	template<class T = Component>
	T* GetComponent() 
	{
		for (Component* component : components)
		{
			T* castedComponent = dynamic_cast<T*>(component);
			if (castedComponent == nullptr) 
			{
				continue;
			}
			return castedComponent;
		}
		return nullptr;
	}
	void RemoveComponent(Component* component);	
	void SetActive(const bool active);

private:	
	void _UpdateComponents(const float deltaTime);
};
#endif // GAMEOBJECT_H
