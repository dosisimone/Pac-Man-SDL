#ifndef PLAYERBEHAVIOURCOMPONENT_H
#define PLAYERBEHAVIOURCOMPONENT_H

#include "Component.h"
#include "../EventSystem/Events.h"

class SpriteAnimationComponent;
class TileMapPositionComponent;
class TileMovementComponent;
class TeleportComponent;

class PlayerBehaviourComponent : public Component, 
	// listeners
	CollisionEventListener, 
	// dispatchers
	SimpleDotCollectedEventDispatcher, BigDotCollectedEventDispatcher, PlayerDeathEventDispatcher, GhostKilledEventDispatcher
{
private:		
	SpriteAnimationComponent* animationRenderer = nullptr;
	TileMapPositionComponent* tilePosition = nullptr;
	TileMovementComponent* tileMovement = nullptr;
	TeleportComponent* teleportedTo = nullptr;
	int previousValidInputX = -1;
	int previousValidInputY = 0;

public:
	PlayerBehaviourComponent();
	~PlayerBehaviourComponent() override;
	void Awake() override;
	void Start() override;	
	//events
	void OnEvent(const CollisionEventArgs& event, const CollisionEventDispatcher& sender) override;	
	void Subscribe(SimpleDotCollectedEventListener* listener) { SimpleDotCollectedEventDispatcher::Subscribe(listener); }
	void Unsubscribe(SimpleDotCollectedEventListener* listener) { SimpleDotCollectedEventDispatcher::Unsubscribe(listener); }
	void Subscribe(BigDotCollectedEventListener* listener) { BigDotCollectedEventDispatcher::Subscribe(listener); }
	void Unsubscribe(BigDotCollectedEventListener* listener) { BigDotCollectedEventDispatcher::Unsubscribe(listener); }
	void Subscribe(PlayerDeathEventListener* listener) { PlayerDeathEventDispatcher::Subscribe(listener); }
	void Unsubscribe(PlayerDeathEventListener* listener) { PlayerDeathEventDispatcher::Unsubscribe(listener); }
	void Subscribe(GhostKilledEventListener* listener) { GhostKilledEventDispatcher::Subscribe(listener); }
	void Unsubscribe(GhostKilledEventListener* listener) { GhostKilledEventDispatcher::Unsubscribe(listener); }

protected:
	void _Update(const float& deltaTime) override;

private:
	void _SimpleDotCollected();
	void _BigDotCollected();
	void _Death();
	bool _IsPlayerWalkable(const unsigned int x, const unsigned int y) const;
};
#endif // PLAYERBEHAVIOURCOMPONENT_H
