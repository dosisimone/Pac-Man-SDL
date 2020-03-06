#ifndef EVENTS_H
#define EVENTS_H

class GameObject;

struct CollisionEventArgs 
{
	GameObject* hitObject;
};

#endif // EVENTS_H