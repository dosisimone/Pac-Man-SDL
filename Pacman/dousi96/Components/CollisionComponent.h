#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include <vector>
#include <map> 
#include "Component.h"
#include "../EventSystem/Events.h"

class CollisionComponent : public Component, CollisionEventDispatcher 
{
private:
	std::vector<GameObject*> targets;
	std::map<GameObject*, CollisionStatus> collisionsStatus;

public:
	CollisionComponent();
	~CollisionComponent();
	void Start() override;
	void Update(const float deltaTime) override;
	void AddTarget(GameObject* newTarget);
	void Subscribe(CollisionEventListener* listener) { CollisionEventDispatcher::Subscribe(listener); }
	void Unsubscribe(CollisionEventListener* listener) { CollisionEventDispatcher::Unsubscribe(listener); }
};
#endif // COLLISIONCOMPONENT_H