#ifndef PLAYERBEHAVIOURCOMPONENT_H
#define PLAYERBEHAVIOURCOMPONENT_H

#include "Component.h"
#include "CollisionComponent.h"
#include "../EventSystem/Events.h"

class SpriteAnimationComponent;
class TileMapPositionComponent;
class TileMovementComponent;
class TeleportComponent;

class PlayerBehaviourComponent : public Component, CollisionEventListener, DotCollectedEventDispatcher
{
private:		
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
	virtual void OnEvent(const CollisionEventArgs& event, const CollisionEventDispatcher& sender) override;
	void Subscribe(DotCollectedEventListener* listener) { DotCollectedEventDispatcher::Subscribe(listener); }
	void Unsubscribe(DotCollectedEventListener* listener) { DotCollectedEventDispatcher::Unsubscribe(listener); }

};
#endif // PLAYERBEHAVIOURCOMPONENT_H
