#ifndef GHOSTBEHAVIOURCOMPONENT_H
#define GHOSTBEHAVIOURCOMPONENT_H

#include "Component.h"
#include "../EventSystem/Events.h"
#include "../Timer.h"

class SpriteAnimationComponent;
class TileMapPositionComponent;
class TileMovementComponent;
class GhostPathfinderComponent;
class TeleportComponent;
struct Tile;

class GhostBehaviourComponent : public Component, BigDotCollectedEventListener
{
public:
	enum class GhostStatus : short
	{
		Chase,
		Scatter,
		Frightened,
		Dead,
		Paused,
		LeavingHouse
	};

private:
	GhostStatus status = GhostStatus::Paused;
	Timer statusTimer;
	int statusPhaseIndex = 0;
	Tile* ghostHouseTile = nullptr;
	Tile* scatterStatusTarget = nullptr;

	SpriteAnimationComponent* animationRenderer = nullptr;
	TileMapPositionComponent* tilePosition = nullptr;
	TileMovementComponent* tileMovement = nullptr;
	GhostPathfinderComponent* pathfinder = nullptr;

public:
	GhostBehaviourComponent();
	~GhostBehaviourComponent() override;
	void Awake() override;
	void Start() override;	
	GhostStatus GetStatus() const;
	void ForceTimer(const float seconds);
	void SetGhostHouseTile(const unsigned int x, const unsigned int y);
	void SetScatterStatusTarget(const unsigned int x, const unsigned int y);
	void Kill();
	void OnEvent(const BigDotCollectedEventArgs& event, const BigDotCollectedEventDispatcher& sender) override;

protected:
	void _Update(const float& deltaTime) override;

private:
	void _NextStatus();
	void _SetPausedStatus();
	void _SetChaseStatus();
	void _SetScatterStatus();
	void _SetFrightenedStatus();
	void _SetLeavingGhostHouseStatus();
	Tile* _GetRandomPlayerWalkableTile() const;
};
#endif // GHOSTBEHAVIOURCOMPONENT_H