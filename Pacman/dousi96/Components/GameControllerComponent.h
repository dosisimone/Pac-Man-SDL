#ifndef GAMECONTROLLERCOMPONENT_H
#define GAMECONTROLLERCOMPONENT_H

#include "Component.h"
#include "../GameObject.h"
#include "../Timer.h"
#include "../EventSystem/Events.h"

class TileMap;
class PlayerBehaviourComponent;
class GhostBehaviourComponent;

class GameControllerComponent : public Component, 
	//listeners
	PlayerDeathEventListener, SimpleDotCollectedEventListener, BigDotCollectedEventListener, GhostKilledEventListener,
	//dispatchers
	LivesValueUpdatedEventDispatcher, PointsValueUpdatedEventDispatcher
{
public:
	enum class GameState : short
	{
		Paused,
		Playing,
		GameOver
	};

private:
	unsigned short lives = 0;
	unsigned int points = 0;
	unsigned int totDotsOnMap = 0;
	GameState state = GameState::Paused;
	Timer changeStateTimer;

	TileMap* tileMap = nullptr;
	PlayerBehaviourComponent* playerBehaviour = nullptr;
	std::vector<GhostBehaviourComponent*> ghostBehaviours;

public:
	GameControllerComponent();
	~GameControllerComponent() override;
	void Awake() override;
	void Start() override;	
	void SetDurationChangeState(const float duration);
	TileMap* GetTileMap() const;
	//events
	void OnEvent(const PlayerDeathEventArgs& event, const PlayerDeathEventDispatcher& sender) override;
	void OnEvent(const SimpleDotCollectedEventArgs& event, const SimpleDotCollectedEventDispatcher& sender) override;
	void OnEvent(const BigDotCollectedEventArgs& event, const BigDotCollectedEventDispatcher& sender) override;
	void OnEvent(const GhostKilledEventArgs& event, const GhostKilledEventDispatcher& sender) override;
	void Subscribe(LivesValueUpdatedEventListener* listener) { LivesValueUpdatedEventDispatcher::Subscribe(listener); }
	void Unsubscribe(LivesValueUpdatedEventListener* listener) { LivesValueUpdatedEventDispatcher::Unsubscribe(listener); }
	void Subscribe(PointsValueUpdatedEventListener* listener) { PointsValueUpdatedEventDispatcher::Subscribe(listener); }
	void Unsubscribe(PointsValueUpdatedEventListener* listener) { PointsValueUpdatedEventDispatcher::Unsubscribe(listener); }

protected:
	void _Update(const float& deltaTime) override;

private:
	void _LoadMap();	
	void _InstanceMapObjects();
	void _InstanceUIObjects();
	void _InstancePlayer();
	void _InstanceGhosts();
	void _GameOver();
	void _PlayerWin();
	void _ResetGame();
	void _AddPoints(const unsigned int pointsToAdd);
};
#endif // GAMECONTROLLERCOMPONENT_H