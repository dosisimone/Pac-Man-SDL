#ifndef PLAYERBEHAVIOURCOMPONENT_H
#define PLAYERBEHAVIOURCOMPONENT_H

#include "Component.h"
#include "Collider/CollisionComponent.h"
#include "../EventSystem/Events.h"

class SpriteAnimationComponent;
class TileMapPositionComponent;
class TileMovementComponent;
class TeleportComponent;

class PlayerBehaviourComponent : public Component, 
	CollisionEventListener, 
	PointsValueUpdatedEventDispatcher, LivesValueUpdatedEventDispatcher, BigDotCollectedEventDispatcher
{
private:		
	unsigned int points = 0;
	unsigned int lives = 2;
	float speed = 1.0f;	
	SpriteAnimationComponent* animationRenderer = nullptr;
	TileMapPositionComponent* tilePosition = nullptr;
	TileMovementComponent* tileMovement = nullptr;
	TeleportComponent* teleportedTo = nullptr;

public:
	PlayerBehaviourComponent();
	~PlayerBehaviourComponent() override;
	void Start() override;	
	void SetSpeed(const float speed);
	unsigned int GetLives() const;
	unsigned int GetPoints() const;
	//events
	void OnEvent(const CollisionEventArgs& event, const CollisionEventDispatcher& sender) override;	
	void Subscribe(PointsValueUpdatedEventListener* listener) { PointsValueUpdatedEventDispatcher::Subscribe(listener); }
	void Unsubscribe(PointsValueUpdatedEventListener* listener) { PointsValueUpdatedEventDispatcher::Unsubscribe(listener); }
	void Subscribe(LivesValueUpdatedEventListener* listener) { LivesValueUpdatedEventDispatcher::Subscribe(listener); }
	void Unsubscribe(LivesValueUpdatedEventListener* listener) { LivesValueUpdatedEventDispatcher::Unsubscribe(listener); }
	void Subscribe(BigDotCollectedEventListener* listener) { BigDotCollectedEventDispatcher::Subscribe(listener); }
	void Unsubscribe(BigDotCollectedEventListener* listener) { BigDotCollectedEventDispatcher::Unsubscribe(listener); }

protected:
	void _Update(const float& deltaTime) override;

private:
	void _AddPoints(const unsigned int pointsToAdd);
	void _BigDotCollected();
	void _Death();
};
#endif // PLAYERBEHAVIOURCOMPONENT_H
