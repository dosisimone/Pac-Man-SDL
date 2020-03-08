#ifndef GHOSTBEHAVIOURCOMPONENT_H
#define GHOSTBEHAVIOURCOMPONENT_H

#include "Component.h"
#include "Collider/CollisionComponent.h"
#include "../EventSystem/Events.h"
#include "../Timer.h"

class SpriteAnimationComponent;
class TileMapPositionComponent;
class TileMovementComponent;
class TeleportComponent;

class GhostBehaviourComponent : public Component
{
public:
	enum class GhostStatus : short
	{
		Chase,
		Scatter,
		Frightened,
		Dead,
		Paused
	};

private:
	GhostStatus status = GhostStatus::Paused;
	float speed = 1.0f;
	Timer frightenedStatusTimer;

	SpriteAnimationComponent* animationRenderer = nullptr;
	TileMapPositionComponent* tilePosition = nullptr;
	TileMovementComponent* tileMovement = nullptr;
	TeleportComponent* teleportedTo = nullptr;

public:
	GhostBehaviourComponent();
	~GhostBehaviourComponent() override;
	void Start() override;	
	GhostStatus GetStatus() const;

protected:
	void _Update(const float& deltaTime) override;
};
#endif // GHOSTBEHAVIOURCOMPONENT_H