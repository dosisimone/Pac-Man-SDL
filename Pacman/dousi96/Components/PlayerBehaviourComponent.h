#ifndef PLAYERBEHAVIOURCOMPONENT_H
#define PLAYERBEHAVIOURCOMPONENT_H

#include "Component.h"
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
	SpriteAnimationComponent* animationRenderer = nullptr;
	TileMapPositionComponent* tilePosition = nullptr;
	TileMovementComponent* tileMovement = nullptr;
	TeleportComponent* teleportedTo = nullptr;
	int previousValidInputX = 0;
	int previousValidInputY = 0;

public:
	PlayerBehaviourComponent();
	~PlayerBehaviourComponent() override;
	void Awake() override;
	void Start() override;	
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
	bool _IsPlayerWalkable(const unsigned int x, const unsigned int y) const;
};
#endif // PLAYERBEHAVIOURCOMPONENT_H
