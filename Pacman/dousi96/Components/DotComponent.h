#ifndef DOTCOMPONENT_H
#define DOTCOMPONENT_H

#include "Component.h"

class DotComponent : public Component
{
private:
	unsigned int pointsToAdd = 0;

public:
	DotComponent();
	~DotComponent() override;
	void Start() override {}
	void Update(const float deltaTime) override {}
	unsigned int GetPointsToAdd() const;
	void SetPointsToAdd(const unsigned int pointsToAdd);	
};
#endif // DOTCOMPONENT_H