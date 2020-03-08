#include "GameControllerComponent.h"
#include <vector>
#include "../GameController.h"
#include "PlayerBehaviourComponent.h"
#include "GhostBehaviourComponent.h"

GameControllerComponent::GameControllerComponent()
{
	this->state = GameState::Paused;
	this->playerBehaviour = nullptr;
}

GameControllerComponent::~GameControllerComponent()
{
}

void GameControllerComponent::Start()
{
	GameObject* playerGameObject = GameController::Instance->GetGameObjectByComponent<PlayerBehaviourComponent>();
	this->playerBehaviour = playerGameObject->GetComponent<PlayerBehaviourComponent>();
	this->playerBehaviour->SetActive(false);

	std::vector<GameObject*> ghostGameObjects = GameController::Instance->GetGameObjectsByComponent<GhostBehaviourComponent>();
	for (GameObject* ghostGameObject : ghostGameObjects) 
	{
		GhostBehaviourComponent* ghostBehaviour = ghostGameObject->GetComponent<GhostBehaviourComponent>();
		this->ghostBehaviours.push_back(ghostBehaviour);
		ghostBehaviour->SetActive(false);
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

			playerBehaviour->SetActive(true);







		}
	}
	break;
	}
}
