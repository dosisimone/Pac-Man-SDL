#include "DotComponent.h"

DotComponent::DotComponent()
{
	this->pointsToAdd = 0;
}

DotComponent::~DotComponent()
{
}

unsigned int DotComponent::GetPointsToAdd() const
{
	return this->pointsToAdd;
}

void DotComponent::SetPointsToAdd(const unsigned int pointsToAdd)
{
	this->pointsToAdd = pointsToAdd;
}
