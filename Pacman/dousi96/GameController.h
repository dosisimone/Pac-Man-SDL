#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>
#include "../Vector2f.h"
#include "GameObject.h"

class Drawer;
class GameObject;

class GameController
{
public:
	static GameController* Instance;

private:
	Vector2f input;
	Drawer* drawer;
	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> gameObjectsToDestroy;	

public:
	GameController(Drawer* drawer);
	~GameController();	
	void Start();
	bool Update(const float deltaTime);
	void Draw() const;
	Vector2f GetInput() const;
	Drawer* GetDrawer() const;
	GameObject* CreateGameObject(const Vector2f& position = Vector2f::ZERO);
	void Destroy(GameObject* gameObject);
	std::vector<GameObject*> GetAllGameObjects() const;
	std::vector<GameObject*> GetGameObjectsByTag(const GameObjectTag& tag);
	template<class T = Component>
	std::vector<GameObject*> GetGameObjectsByComponent() 
	{
		std::vector<GameObject*> result;
		for (GameObject* obj : gameObjects) 
		{
			if (obj == nullptr) 
			{
				continue;
			}
			if (obj->GetComponent<T>() != nullptr)
			{
				result.push_back(obj);
			}
		}
		return result;
	}
	template<class T = Component>
	GameObject* GetGameObjectByComponent()
	{
		for (GameObject* obj : gameObjects)
		{
			if (obj == nullptr)
			{
				continue;
			}
			if (obj->GetComponent<T>() != nullptr)
			{
				return obj;
			}
		}
		return nullptr;
	}
	template<class T = Component>
	std::vector<T*> GetComponents() 
	{
		std::vector<T*> result;
		for (GameObject* obj : gameObjects)
		{
			if (obj == nullptr)
			{
				continue;
			}
			T* component = obj->GetComponent<T>();
			if (component != nullptr)
			{
				result.push_back(component);
			}
		}
		return result;
	}
	template<class T = Component>
	T* GetComponent()
	{
		for (GameObject* obj : gameObjects)
		{
			if (obj == nullptr)
			{
				continue;
			}
			T* component = obj->GetComponent<T>();
			if (component != nullptr)
			{
				return component;
			}
		}
		return nullptr;
	}

private:	
	bool _UpdateInput();
	void _DestroyScheduledGameObjects();
};

#endif // GAMECONTROLLER_H
