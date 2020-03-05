#ifndef COMPONENT_H
#define COMPONENT_H

#include "../GameObject.h"

class Component 
{
public:
	enum ComponentType
	{
		None = 0,
		Renderer = 1,
		Collider = 2,
	};

public:
	GameObject* Owner = nullptr;

public:
	Component() = default;
	~Component() = default;
	void Register(GameObject* gameObject);
	virtual void Update(const float deltaTime) {};
	virtual void Draw() const {};
	virtual ComponentType GetType() const { return ComponentType::None; };
};
#endif // COMPONENT_H
