#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>
#include "../Vector2f.h"
#include "TileMap.h"

class Drawer;
class GameObject;

class GameController
{
public:
	static GameController* Instance;

private:
	Drawer* drawer;
	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> gameObjectsToDestroy;
	Vector2f input;
	TileMap* tileMap;	

public:
	GameController(Drawer* drawer);
	~GameController();	
	void Start();
	bool Update(const float deltaTime);
	void Draw() const;
	Vector2f GetInput() const;
	Drawer* GetDrawer() const;
	TileMap* GetTileMap() const;
	GameObject* CreateGameObject(const Vector2f& position = Vector2f::ZERO);
	void Destroy(GameObject* gameObject);
	/*std::vector<GameObject*> GetGameObjectsByTag(const GameObjectTag& tag) const;*/

private:	
	bool _UpdateInput();
	void _DestroyScheduledGameObjects();
};

#endif // GAMECONTROLLER_H
