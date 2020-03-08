#ifndef GHOSTBEHAVIOURCOMPONENT_H
#define GHOSTBEHAVIOURCOMPONENT_H

#include "Component.h"
#include "../EventSystem/Events.h"
#include "../Timer.h"

class SpriteAnimationComponent;
class TileMapPositionComponent;
class TileMovementComponent;
class TeleportComponent;

class GhostBehaviourComponent : public Component, BigDotCollectedEventListener
{
public:
	enum class GhostStatus : short
	{
		Chase,
		Frightened,
		Dead,
		Paused
	};

private:
	GhostStatus status = GhostStatus::Paused;
	Timer statusTimer;

	SpriteAnimationComponent* animationRenderer = nullptr;
	TileMapPositionComponent* tilePosition = nullptr;
	TileMovementComponent* tileMovement = nullptr;
	TeleportComponent* teleportedTo = nullptr;

public:
	GhostBehaviourComponent();
	~GhostBehaviourComponent() override;
	void Start() override;	
	GhostStatus GetStatus() const;
	void OnEvent(const BigDotCollectedEventArgs& event, const BigDotCollectedEventDispatcher& sender) override;

protected:
	void _Update(const float& deltaTime) override;

private:
	void _SetChaseStatus();
	void _SetFrightenedStatus();
};
#endif // GHOSTBEHAVIOURCOMPONENT_H