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

protected:
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
	void Kill();
	void OnEvent(const BigDotCollectedEventArgs& event, const BigDotCollectedEventDispatcher& sender) override;

protected:
	void _Update(const float& deltaTime) override;
	virtual void _InitAnimations() = 0;
	virtual Tile* _GetGhostHouseTargetTile() const = 0;
	virtual Tile* _GetScatterTargetTile() const = 0;
	virtual Tile* _GetChaseTargetTile() const = 0;

private:
	void _NextStatus();
	void _SetPausedStatus();
	void _SetChaseStatus();
	void _SetScatterStatus();
	void _SetFrightenedStatus();
	void _SetLeavingGhostHouseStatus();
	Tile* _GetRandomPlayerWalkableTile() const;
};

class RedGhostBehaviourComponent : public GhostBehaviourComponent 
{
protected:
	void _InitAnimations() override;
	Tile* _GetGhostHouseTargetTile() const override;
	Tile* _GetScatterTargetTile() const override;
	Tile* _GetChaseTargetTile() const override;
};

class BlueGhostBehaviourComponent : public GhostBehaviourComponent
{
protected:
	void _InitAnimations() override;
	Tile* _GetGhostHouseTargetTile() const override;
	Tile* _GetScatterTargetTile() const override;
	Tile* _GetChaseTargetTile() const override;
};

class PinkGhostBehaviourComponent : public GhostBehaviourComponent
{
protected:
	void _InitAnimations() override;
	Tile* _GetGhostHouseTargetTile() const override;
	Tile* _GetScatterTargetTile() const override;
	Tile* _GetChaseTargetTile() const override;
};

class OrangeGhostBehaviourComponent : public GhostBehaviourComponent
{
protected:
	void _InitAnimations() override;
	Tile* _GetGhostHouseTargetTile() const override;
	Tile* _GetScatterTargetTile() const override;
	Tile* _GetChaseTargetTile() const override;
};
#endif // GHOSTBEHAVIOURCOMPONENT_H
