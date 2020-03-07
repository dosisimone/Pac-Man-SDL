#ifndef EVENTS_H
#define EVENTS_H

#include "EventSystem.h"

class GameObject;

enum class CollisionStatus : short
{
	Enter,
	Stay,
	Exit
};


struct CollisionEventArgs 
{	
	GameObject* sender;
	GameObject* hit;
	CollisionStatus status;
};

typedef EventDispatcher<CollisionEventArgs> CollisionEventDispatcher;
typedef EventDispatcher<CollisionEventArgs>::Listener CollisionEventListener;

#endif // EVENTS_H