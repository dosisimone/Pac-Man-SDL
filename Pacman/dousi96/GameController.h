#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <list>
#include "../Vector2f.h"
#include "TileMap.h"

class Drawer;
class GameObject;

class GameController
{
private:
	Drawer* drawer;
	std::list<GameObject*> _gameObjects;
	Vector2f input;
	TileMap* tileMap;

public:
	GameController(Drawer* drawer);
	~GameController();	
	void Start();
	bool Update(const float deltaTime);
	void Draw() const;
	Vector2f GetInput() const;

private:	
	bool _UpdateInput();

};
#endif // GAMECONTROLLER_H
