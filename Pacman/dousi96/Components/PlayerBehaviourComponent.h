#ifndef PLAYERBEHAVIOURCOMPONENT_H
#define PLAYERBEHAVIOURCOMPONENT_H

#include "Component.h"
#include "CollisionComponent.h"
#include "../EventSystem/Events.h"

class SpriteAnimationComponent;
class TileMapPositionComponent;
class TileMovementComponent;
class TeleportComponent;

class PlayerBehaviourComponent : public Component, CollisionEventListener, PointsValueUpdatedEventDispatcher
{
private:		
	unsigned int points = 0;
	float speed = 1.0f;	
	SpriteAnimationComponent* animationRenderer = nullptr;
	TileMapPositionComponent* tilePosition = nullptr;
	TileMovementComponent* tileMovement = nullptr;
	Vector2f oldValidInput = Vector2f::ZERO; 
	TeleportComponent* teleportedTo = nullptr;

public:
	PlayerBehaviourComponent();
	~PlayerBehaviourComponent() override;
	void Start() override;
	void Update(const float deltaTime) override;
	void SetSpeed(const float speed);
	void OnEvent(const CollisionEventArgs& event, const CollisionEventDispatcher& sender) override;
	void Subscribe(PointsValueUpdatedEventListener* listener) { PointsValueUpdatedEventDispatcher::Subscribe(listener); }
	void Unsubscribe(PointsValueUpdatedEventListener* listener) { PointsValueUpdatedEventDispatcher::Unsubscribe(listener); }
};
#endif // PLAYERBEHAVIOURCOMPONENT_H
