#ifndef GAMECONTROLLERCOMPONENT_H
#define GAMECONTROLLERCOMPONENT_H

#include "Component.h"
#include "../GameObject.h"
#include "../Timer.h"

class TileMap;
class PlayerBehaviourComponent;
class GhostBehaviourComponent;

class GameControllerComponent : public Component
{
public:
	enum class GameState : short
	{
		Paused,
		Playing,
		Restart,
		GameOver
	};

private:
	TileMap* tileMap = nullptr;

	GameState state = GameState::Paused;
	Timer changeStateTimer;

	PlayerBehaviourComponent* playerBehaviour = nullptr;
	std::vector<GhostBehaviourComponent*> ghostBehaviours;

public:
	GameControllerComponent();
	~GameControllerComponent() override;
	void Start() override;	
	void SetDurationChangeState(const float duration);
	TileMap* GetTileMap() const;

protected:
	void _Update(const float& deltaTime) override;

private:
	void _LoadMap();	
	void _InstanceMapObjects();
	void _InstanceUIObjects();
	void _InstancePlayer();
	void _InstanceGhosts();
};
#endif // GAMECONTROLLERCOMPONENT_H