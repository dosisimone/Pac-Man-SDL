#ifndef TELEPORTCOMPONENT_H
#define TELEPORTCOMPONENT_H

#include "Component.h"

class TeleportComponent : public Component
{
private:
	TeleportComponent* other = nullptr;

public:
	TeleportComponent();
	~TeleportComponent();
	void Start() override {}
	void Update(const float deltaTime) override {}
	TeleportComponent* GetLinkedTeleport();
	void SetLinkedTeleport(TeleportComponent* other);
};
#endif // TELEPORTCOMPONENT_H