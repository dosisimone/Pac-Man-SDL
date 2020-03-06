#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "../Vector2f.h"

class Component;
class RendererComponent;
class GameController;
enum ComponentType;

class GameObject
{
public:	
	Vector2f Position;

private:	
	GameController* controller = nullptr;
	bool isActive = false;
	std::vector<Component*> components;	

public:
	~GameObject();	
	void Draw() const;
	void Update(const float deltaTime);

	template<class T = Component>
	T* AddComponent() 
	{
		T* component = new T();
		component->Register(this);
		components.emplace_back(component);
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
	GameController* GetController() const;
	void SetActive(const bool active);

	static GameObject* CreateGameObject(GameController* controller, const Vector2f& position = Vector2f::ZERO);

private:
	GameObject(const Vector2f& position);
	void _Register(GameController* controller);
	void _UpdateComponents(const float deltaTime);
};
#endif // GAMEOBJECT_H
