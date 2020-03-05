#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include "../Vector2f.h"

class Component;
class RendererComponent;
enum ComponentType;

class GameObject
{
public:	
	Vector2f Position;

private:	
	bool isActive;
	std::list<Component*> components;	

public:
	GameObject();
	GameObject(const Vector2f& position);
	~GameObject() = default;
	void Draw() const;
	virtual void Update(const float deltaTime);

	template<class T=Component>
	T* AddComponent() 
	{
		T* component = new T();
		component->Register(this);
		components.push_back(component);
		return component;
	}

	Component* GetComponentByType(const ComponentType type);
	void RemoveComponent(Component* component);	
	void SetActive(const bool active);

private:
	void _UpdateComponents(const float deltaTime);
};
#endif // GAMEOBJECT_H