#include "PlayerBehaviourComponent.h"

void PlayerBehaviourComponent::Update(const float deltaTime)
{
	const Vector2f kInput = gameController->GetInput();
	Owner->Position += kInput * speed * deltaTime;

	
}

void PlayerBehaviourComponent::SetGameController(GameController* gameController)
{
	this->gameController = gameController;
}

void PlayerBehaviourComponent::SetSpeed(const float speed)
{
	if (speed <= 0.0f) 
	{
		return;
	}
	this->speed = speed;
}
