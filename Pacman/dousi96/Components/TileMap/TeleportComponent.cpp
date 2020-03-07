#include "TeleportComponent.h"
#include <vector>
#include "../../GameController.h"

TeleportComponent::TeleportComponent()
{
	this->other = nullptr;
}

TeleportComponent::~TeleportComponent()
{
}

TeleportComponent* TeleportComponent::GetLinkedTeleport()
{
	return this->other;
}

void TeleportComponent::SetLinkedTeleport(TeleportComponent* otherTeleport)
{
	if (otherTeleport == nullptr) 
	{
		return;
	}
	this->other = otherTeleport;
}
