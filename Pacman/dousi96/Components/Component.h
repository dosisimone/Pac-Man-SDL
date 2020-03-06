#ifndef COMPONENT_H
#define COMPONENT_H

#include "../GameObject.h"

class Component 
{
public:
	GameObject* Owner = nullptr;

public:
	Component() = default;
	~Component() = default;
	void Register(GameObject* gameObject);
	virtual void Start() {};
	virtual void Update(const float deltaTime) {};
	virtual void Draw() const {};
};

#endif // COMPONENT_H
