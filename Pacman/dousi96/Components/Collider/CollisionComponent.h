#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include <vector>
#include <map> 
#include "../Component.h"
#include "../../EventSystem/Events.h"

class CollisionComponent : public Component, CollisionEventDispatcher 
{
private:
	std::vector<GameObject*> targets;
	std::map<GameObject*, CollisionStatus> collisionsStatus;

public:
	CollisionComponent();
	~CollisionComponent() override;
	void Start() override;	
	void AddTarget(GameObject* newTarget);
	void Subscribe(CollisionEventListener* listener) { CollisionEventDispatcher::Subscribe(listener); }
	void Unsubscribe(CollisionEventListener* listener) { CollisionEventDispatcher::Unsubscribe(listener); }

protected:
	void _Update(const float& deltaTime) override;
};
#endif // COLLISIONCOMPONENT_H