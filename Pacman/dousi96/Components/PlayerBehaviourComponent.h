#ifndef PLAYERMOVEMENTCOMPONENT_H
#define PLAYERMOVEMENTCOMPONENT_H

#include "Component.h"
#include "../../Drawer.h"
#include "../GameController.h"

class PlayerBehaviourComponent : public Component
{
private:
	GameController* gameController;
	float speed = 1.0f;

public:
	PlayerBehaviourComponent() = default;
	~PlayerBehaviourComponent() = default;
	virtual void Update(const float deltaTime) override;
	void SetGameController(GameController* gameController);
	void SetSpeed(const float speed);
};
#endif // PLAYERMOVEMENTCOMPONENT_H