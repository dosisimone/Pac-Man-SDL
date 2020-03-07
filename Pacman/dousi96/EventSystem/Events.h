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

struct PointsValueUpdatedEventArgs 
{
	unsigned int points;
};
typedef EventDispatcher<PointsValueUpdatedEventArgs> PointsValueUpdatedEventDispatcher;
typedef EventDispatcher<PointsValueUpdatedEventArgs>::Listener PointsValueUpdatedEventListener;

struct LivesValueUpdatedEventArgs
{
	unsigned int lives;
};
typedef EventDispatcher<LivesValueUpdatedEventArgs> LivesValueUpdatedEventDispatcher;
typedef EventDispatcher<LivesValueUpdatedEventArgs>::Listener LivesValueUpdatedEventListener;

struct BigDotCollectedEventArgs
{
};
typedef EventDispatcher<BigDotCollectedEventArgs> BigDotCollectedEventDispatcher;
typedef EventDispatcher<BigDotCollectedEventArgs>::Listener BigDotCollectedEventListener;

#endif // EVENTS_H