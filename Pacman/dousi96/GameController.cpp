#include "SDL.h"
#include "GameController.h"
#include "GameObject.h"
#include "Components/UI/UITextComponent.h"
#include "Components/UI/UIPointsLabelComponent.h"
#include "Components/UI/UILivesLabelComponent.h"
#include "Components/GameControllerComponent.h"

GameController* GameController::Instance = nullptr;

GameController::GameController(Drawer* drawer)
{
	this->Instance = this;
	this->drawer = drawer;
	this->input = Vector2f::LEFT;
}

GameController::~GameController()
{
	for (unsigned int i = 0; i < gameObjects.size(); ++i)
	{
		Destroy(gameObjects[i]);
	}
	_DestroyScheduledGameObjects();
}

void GameController::Start()
{
	//load the map
	{
		
	}

	//background object
	{
		
	}

	//UI
	UIPointsLabelComponent* pointsLabelUIComponent;
	UILivesLabelComponent* livesLabelUIComponent;
	{
		GameObject* scoreLabelTextUIObject = CreateGameObject();
		scoreLabelTextUIObject->Tag = GameObjectTag::UI;
		UITextComponent* scoreLabelTextUIComponent = scoreLabelTextUIObject->AddComponent<UITextComponent>();
		scoreLabelTextUIComponent->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
		scoreLabelTextUIComponent->SetScreenPosition(20, 50);
		scoreLabelTextUIComponent->SetText("Score: ");

		GameObject* scoreLabelValueUIObject = CreateGameObject();
		scoreLabelValueUIObject->Tag = GameObjectTag::UI;
		UITextComponent* scoreLabelValueUIComponent = scoreLabelValueUIObject->AddComponent<UITextComponent>();
		scoreLabelValueUIComponent->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
		scoreLabelValueUIComponent->SetScreenPosition(110, 50);
		scoreLabelValueUIComponent->SetText("0");
		pointsLabelUIComponent = scoreLabelValueUIObject->AddComponent<UIPointsLabelComponent>();

		GameObject* livesLabelTextUIObject = CreateGameObject();
		livesLabelTextUIObject->Tag = GameObjectTag::UI;
		UITextComponent* livesLabelTextUIComponent = livesLabelTextUIObject->AddComponent<UITextComponent>();
		livesLabelTextUIComponent->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
		livesLabelTextUIComponent->SetScreenPosition(20, 90);
		livesLabelTextUIComponent->SetText("Lives: ");

		GameObject* livesLabelValueUIObject = CreateGameObject();
		livesLabelValueUIObject->Tag = GameObjectTag::UI;
		UITextComponent* livesLabelValueUIComponent = livesLabelValueUIObject->AddComponent<UITextComponent>();
		livesLabelValueUIComponent->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
		livesLabelValueUIComponent->SetScreenPosition(110, 90);
		livesLabelValueUIComponent->SetText("2");
		livesLabelUIComponent = livesLabelValueUIObject->AddComponent<UILivesLabelComponent>();
	}

	//init game controller component
	{
		GameObject* gameController = CreateGameObject();
		gameController->Tag = GameObjectTag::Logic;
		GameControllerComponent* gameControllerComponent = gameController->AddComponent<GameControllerComponent>();
		gameControllerComponent->SetDurationChangeState(3.f);
	}
}

bool GameController::Update(const float deltaTime)
{
	if (!_UpdateInput())
	{
		return false;
	}

	for (GameObject* obj : gameObjects)
	{
		obj->Update(deltaTime);
	}

	_DestroyScheduledGameObjects();

	return true;
}

void GameController::Draw() const
{
	for (GameObject* obj : gameObjects)
	{
		obj->Draw();
	}
}

Vector2f GameController::GetInput() const
{
	return input;
}

Drawer* GameController::GetDrawer() const
{
	return drawer;
}

GameObject* GameController::CreateGameObject(const Vector2f& position)
{
	GameObject* gameObject = new GameObject(position);
	gameObjects.push_back(gameObject);
	return gameObject;
}

void GameController::Destroy(GameObject* gameObject)
{
	if (gameObject == nullptr) 
	{
		return;
	}
	gameObject->SetActive(false);
	gameObjectsToDestroy.push_back(gameObject);
}

std::vector<GameObject*> GameController::GetGameObjectsByTag(const GameObjectTag& tag)
{
	std::vector<GameObject*> result;
	for (GameObject* obj : gameObjects)
	{
		if (obj == nullptr)
		{
			continue;
		}
		if (obj->Tag == tag)
		{
			result.push_back(obj);
		}
	}
	return result;
}

bool GameController::_UpdateInput()
{
	input = Vector2f::ZERO;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_ESCAPE])
	{
		return false;
	}

	if (keystate[SDL_SCANCODE_UP])
	{
		input = Vector2f::UP;
	}
	else if (keystate[SDL_SCANCODE_DOWN])
	{
		input = Vector2f::DOWN;
	}
	else if (keystate[SDL_SCANCODE_RIGHT])
	{
		input = Vector2f::RIGHT;
	}
	else if (keystate[SDL_SCANCODE_LEFT])
	{
		input = Vector2f::LEFT;
	}
	return true;
}

void GameController::_DestroyScheduledGameObjects()
{
	for (unsigned int i = 0; i < gameObjectsToDestroy.size(); ++i) 
	{
		for (unsigned int j = 0; j < gameObjects.size(); ++j) 
		{
			if (gameObjects[j] == gameObjectsToDestroy[i]) 
			{
				gameObjects.erase(gameObjects.begin() + j);
				break;
			}
		}

		delete gameObjectsToDestroy[i];
		gameObjectsToDestroy[i] = nullptr;
	}
	gameObjectsToDestroy.clear();
}
