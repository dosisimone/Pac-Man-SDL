#include "GhostBehaviourComponent.h"

GhostBehaviourComponent::GhostBehaviourComponent()
{
}

GhostBehaviourComponent::~GhostBehaviourComponent()
{
}

void GhostBehaviourComponent::Start()
{
}


GhostBehaviourComponent::GhostStatus GhostBehaviourComponent::GetStatus() const
{
	return this->status;
}

void GhostBehaviourComponent::_Update(const float& deltaTime)
{
	if (!IsActive())
	{
		return;
	}

}
