#ifndef PACMAN_H
#define PACMAN_H

#include <list>
#include "Vector2f.h"
#include "dousi96/GameObject.h"

struct SDL_Surface;
class Drawer;
class Avatar;
class World;
class Ghost;
class GameObject;

class Pacman
{
private:
	std::list<GameObject*> _gameObjects;
	GameObject* player;

public:
	static Pacman* Create(Drawer* aDrawer);
	~Pacman(void);

	bool Update(float aTime);
	bool Draw();

private:
	Pacman(Drawer* aDrawer);
	bool Init();
	bool UpdateInput();
	void MoveAvatar();
	bool CheckEndGameCondition();

	Drawer* myDrawer;

	float myTimeToNextUpdate;
	float myGhostGhostCounter;

	int myLives;
	int myScore;
	int myFps;

	Vector2f myNextMovement;

	Avatar* myAvatar;
	Ghost* myGhost;
	World* myWorld;
};

#endif // PACMAN_H