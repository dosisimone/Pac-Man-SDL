#include "GameControllerComponent.h"
#include <vector>
#include "../GameController.h"
#include "PlayerBehaviourComponent.h"
#include "GhostBehaviourComponent.h"

GameControllerComponent::GameControllerComponent()
{
	this->state = GameState::Paused;
	this->playerObject = nullptr;
}

GameControllerComponent::~GameControllerComponent()
{
}

void GameControllerComponent::Start()
{
	playerObject = GameController::Instance->GetGameObjectByComponent<PlayerBehaviourComponent>();
	playerObject->SetActive(false);

	std::vector<GameObject*> ghostGameObjects = GameController::Instance->GetGameObjectsByComponent<GhostBehaviourComponent>();
	for (GameObject* ghostGameObject : ghostGameObjects) 
	{
		ghostObjects.push_back(ghostGameObject);
		ghostGameObject->SetActive(false);
	}
}

void GameControllerComponent::SetDurationChangeState(const float duration)
{
	this->changeStateTimer.SetDuration(duration);
}

void GameControllerComponent::_Update(const float& deltaTime)
{
	changeStateTimer.Increment(deltaTime);

	switch (this->state)
	{
	case GameState::Paused:
	{
		if (changeStateTimer.Check())
		{
			changeStateTimer.Reset();

			playerObject->SetActive(true);







		}
	}
	break;
	}
}
