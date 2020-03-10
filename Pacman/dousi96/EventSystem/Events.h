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
	unsigned short lives;
};
typedef EventDispatcher<LivesValueUpdatedEventArgs> LivesValueUpdatedEventDispatcher;
typedef EventDispatcher<LivesValueUpdatedEventArgs>::Listener LivesValueUpdatedEventListener;

struct SimpleDotCollectedEventArgs
{
};
typedef EventDispatcher<SimpleDotCollectedEventArgs> SimpleDotCollectedEventDispatcher;
typedef EventDispatcher<SimpleDotCollectedEventArgs>::Listener SimpleDotCollectedEventListener;

struct BigDotCollectedEventArgs
{
};
typedef EventDispatcher<BigDotCollectedEventArgs> BigDotCollectedEventDispatcher;
typedef EventDispatcher<BigDotCollectedEventArgs>::Listener BigDotCollectedEventListener;

struct PlayerDeathEventArgs
{
};
typedef EventDispatcher<PlayerDeathEventArgs> PlayerDeathEventDispatcher;
typedef EventDispatcher<PlayerDeathEventArgs>::Listener PlayerDeathEventListener;

struct GhostKilledEventArgs
{
};
typedef EventDispatcher<GhostKilledEventArgs> GhostKilledEventDispatcher;
typedef EventDispatcher<GhostKilledEventArgs>::Listener GhostKilledEventListener;

#endif // EVENTS_H