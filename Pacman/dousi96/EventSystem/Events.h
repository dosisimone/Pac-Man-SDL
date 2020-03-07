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

struct DotCollectedEventArgs 
{
	unsigned int pointsToAdd;
};

typedef EventDispatcher<DotCollectedEventArgs> DotCollectedEventDispatcher;
typedef EventDispatcher<DotCollectedEventArgs>::Listener DotCollectedEventListener;

#endif // EVENTS_H