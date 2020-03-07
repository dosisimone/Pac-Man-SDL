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
	UI
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
		for (unsigned int i = 0; i < components.size(); ++i)
		{
			T* comp = dynamic_cast<T*>(components[i]);
			if (comp == nullptr) 
			{
				continue;
			}
			return comp;
		}
		return nullptr;
	}
	void RemoveComponent(Component* component);	
	void SetActive(const bool active);

private:	
	void _UpdateComponents(const float deltaTime);
};
#endif // GAMEOBJECT_H
