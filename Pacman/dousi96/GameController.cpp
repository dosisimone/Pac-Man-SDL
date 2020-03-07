#include "SDL.h"
#include "GameController.h"
#include "GameObject.h"
#include "Components/SpriteRendererComponent.h"
#include "Components/PlayerBehaviourComponent.h"
#include "Persistence/TileMapTxtReader.h"
#include "Components/SpriteAnimationComponent.h"
#include "Components/TileMapPositionComponent.h"
#include "Components/TileMovementComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/TeleportComponent.h"
#include "Components/DotComponent.h"
#include "Components/UI/UITextComponent.h"
#include "Components/UI/UIPointsLabelComponent.h"
#include "EventSystem/Events.h"
#include "EventSystem/EventSystem.h"

GameController* GameController::Instance = nullptr;

GameController::GameController(Drawer* drawer)
{
	this->Instance = this;
	this->drawer = drawer;
	this->tileMap = nullptr;
	this->input = Vector2f::LEFT;
}

GameController::~GameController()
{
	delete tileMap;
	tileMap = nullptr;

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
		TileMapTxtReader mapTxtReader;
		tileMap = mapTxtReader.Read("map.txt");
		tileMap->SetDistanceBtwTiles(0.5f);
	}

	//background object
	{
		GameObject* backgroundObject = CreateGameObject();
		backgroundObject->Tag = GameObjectTag::Background;
		SpriteRendererComponent* spriteRenderer = backgroundObject->AddComponent<SpriteRendererComponent>();
		spriteRenderer->SetDrawer(drawer);
		spriteRenderer->SetSprite("playfield.png");
	}

	//UI
	UIPointsLabelComponent* pointsLabelUIComponent;
	{
		GameObject* scoreLabelTextUIObject = CreateGameObject();
		scoreLabelTextUIObject->Tag = GameObjectTag::UI;
		UITextComponent* scoreLabelTextUIComponent = scoreLabelTextUIObject->AddComponent<UITextComponent>();
		scoreLabelTextUIComponent->SetDrawer(drawer);
		scoreLabelTextUIComponent->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
		scoreLabelTextUIComponent->SetScreenPosition(20, 50);
		scoreLabelTextUIComponent->SetText("Score: ");

		GameObject* scoreLabelValueUIObject = CreateGameObject();
		scoreLabelValueUIObject->Tag = GameObjectTag::UI;
		UITextComponent* scoreLabelValueUIComponent = scoreLabelValueUIObject->AddComponent<UITextComponent>();
		scoreLabelValueUIComponent->SetDrawer(drawer);
		scoreLabelValueUIComponent->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
		scoreLabelValueUIComponent->SetScreenPosition(110, 50);
		scoreLabelValueUIComponent->SetText("0");
		pointsLabelUIComponent = scoreLabelValueUIObject->AddComponent<UIPointsLabelComponent>();

		GameObject* livesLabelTextUIObject = CreateGameObject();
		livesLabelTextUIObject->Tag = GameObjectTag::UI;
		UITextComponent* livesLabelTextUIComponent = livesLabelTextUIObject->AddComponent<UITextComponent>();
		livesLabelTextUIComponent->SetDrawer(drawer);
		livesLabelTextUIComponent->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
		livesLabelTextUIComponent->SetScreenPosition(20, 90);
		livesLabelTextUIComponent->SetText("Lives: ");

		GameObject* livesLabelValueUIObject = CreateGameObject();
		livesLabelValueUIObject->Tag = GameObjectTag::UI;
		UITextComponent* livesLabelValueUIComponent = livesLabelValueUIObject->AddComponent<UITextComponent>();
		livesLabelValueUIComponent->SetDrawer(drawer);
		livesLabelValueUIComponent->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
		livesLabelValueUIComponent->SetScreenPosition(110, 90);
		livesLabelValueUIComponent->SetText("0");
	}

	//init tiles
	std::vector<GameObject*> tileObjects;
	{		
		TeleportComponent* firstTeleport = nullptr;
		TeleportComponent* previousTeleport = nullptr;

		float halfSizeTileMapXf = ((float)tileMap->GetSizeX()) / 2.f;
		float halfSizeTileMapYf = ((float)tileMap->GetSizeY()) / 2.f;
		for (unsigned int x = 0; x < tileMap->GetSizeX(); ++x)
		{
			for (unsigned int y = 0; y < tileMap->GetSizeY(); ++y)
			{
				const Tile& tile = tileMap->GetTile(x, y);
				if (!tile.isWalkable)
				{
					continue;
				}

				GameObject* tileObject = CreateGameObject();
				TileMapPositionComponent* tileMapPosition = tileObject->AddComponent<TileMapPositionComponent>();
				tileMapPosition->SetTilePosition(x, y);
				switch (tile.type) 
				{
				case TileType::Dot: 
				{
					tileObject->Tag = GameObjectTag::Dot;
					SpriteRendererComponent* spriteRenderer = tileObject->AddComponent<SpriteRendererComponent>();					
					spriteRenderer->SetDrawer(drawer);
					spriteRenderer->SetSprite("Small_Dot_32.png");
					DotComponent* dot = tileObject->AddComponent<DotComponent>();
					dot->SetPointsToAdd(10);
				}
					break;
				case TileType::BigDot:
				{
					tileObject->Tag = GameObjectTag::BigDot;
					SpriteRendererComponent* spriteRenderer = tileObject->AddComponent<SpriteRendererComponent>();
					spriteRenderer->SetDrawer(drawer);
					spriteRenderer->SetSprite("Big_Dot_32.png");
					DotComponent* dot = tileObject->AddComponent<DotComponent>();
					dot->SetPointsToAdd(50);
				}
					break;
				case TileType::Teleport:
				{
					tileObject->Tag = GameObjectTag::Teleport;
					TeleportComponent* teleportComponent = tileObject->AddComponent<TeleportComponent>();
					if (firstTeleport == nullptr) 
					{
						firstTeleport = teleportComponent;
					}
					else 
					{
						previousTeleport->SetLinkedTeleport(teleportComponent);
					}
					previousTeleport = teleportComponent;
				}
					break;
				}
				tileObjects.push_back(tileObject);
			}
		}

		if (firstTeleport != nullptr && previousTeleport != nullptr && firstTeleport != previousTeleport) 
		{
			previousTeleport->SetLinkedTeleport(firstTeleport);
		}
	}

	//player object
	{
		GameObject* playerObject = CreateGameObject();
		playerObject->Tag = GameObjectTag::Player;
		SpriteRendererComponent* spriteRenderer = playerObject->AddComponent<SpriteRendererComponent>();
		spriteRenderer->SetDrawer(drawer);
		SpriteAnimationComponent* spriteAnimationRenderer = playerObject->AddComponent<SpriteAnimationComponent>();
		SpriteAnimationComponent::Animation defaultPlayerAnimation;
		defaultPlayerAnimation.name = "default";
		defaultPlayerAnimation.sprites = { "open_32.png" , "closed_32.png" },
		defaultPlayerAnimation.secondsBtwFrames = 0.25f;
		spriteAnimationRenderer->AddAnimation(defaultPlayerAnimation);
		spriteAnimationRenderer->SetCurrentAnimation("default");
		TileMapPositionComponent* tileMapPosition = playerObject->AddComponent<TileMapPositionComponent>();
		tileMapPosition->SetTilePosition(13, 7);
		TileMovementComponent* tileMovement = playerObject->AddComponent<TileMovementComponent>();
		tileMovement->SetDestination(12, 7);
		PlayerBehaviourComponent* playerBehaviourComponent = playerObject->AddComponent<PlayerBehaviourComponent>();
		playerBehaviourComponent->SetSpeed(4.f);
		CollisionComponent* collisionComponent = playerObject->AddComponent<CollisionComponent>();
		collisionComponent->Subscribe((CollisionEventListener*)playerBehaviourComponent);
		playerBehaviourComponent->Subscribe((PointsValueUpdatedEventListener*)pointsLabelUIComponent);
		//Init collision system
		for (unsigned int i = 0; i < tileObjects.size(); ++i) 
		{
			collisionComponent->AddTarget(tileObjects[i]);
		}
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

TileMap* GameController::GetTileMap() const
{
	return tileMap;
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

//std::vector<GameObject*> GameController::GetGameObjectsByTag(const GameObjectTag& tag) const
//{
//	std::vector<GameObject*> result;
//	for (GameObject* obj : gameObjects)
//	{
//		if (obj == nullptr)
//		{
//			continue;
//		}
//		if (obj->Tag == tag)
//		{
//			result.push_back(obj);
//		}
//	}
//	return result;
//}

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
