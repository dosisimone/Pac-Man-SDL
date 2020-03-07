#ifndef EVENTS_H
#define EVENTS_H

#include "EventSystem.h"

class GameObject;

struct CollisionEventArgs 
{
	GameObject* sender;
	GameObject* hit;
};

typedef EventDispatcher<CollisionEventArgs> CollisionEventDispatcher;
typedef EventDispatcher<CollisionEventArgs>::Listener CollisionEventListener;

#endif // EVENTS_H