#ifndef PLAYERBEHAVIOURCOMPONENT_H
#define PLAYERBEHAVIOURCOMPONENT_H

#include "Component.h"
#include "CollisionComponent.h"

class SpriteAnimationRendererComponent;
class TileMapPositionComponent;
class TileMovementComponent;

class PlayerBehaviourComponent : public Component, CollisionEventListener
{
private:	
	float speed = 1.0f;	
	SpriteAnimationRendererComponent* animationRenderer = nullptr;
	TileMapPositionComponent* tilePosition = nullptr;
	TileMovementComponent* tileMovement = nullptr;
	Vector2f oldValidInput = Vector2f::ZERO;

public:
	PlayerBehaviourComponent();
	~PlayerBehaviourComponent();
	void Start() override;
	void Update(const float deltaTime) override;
	void SetSpeed(const float speed);

	virtual void OnEvent(const CollisionEventArgs& event, const CollisionEventDispatcher& sender) override;
};
#endif // PLAYERBEHAVIOURCOMPONENT_H
