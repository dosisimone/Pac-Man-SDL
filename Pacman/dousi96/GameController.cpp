#include "SDL.h"
#include "GameController.h"
#include "GameObject.h"
#include "Components/SpriteRendererComponent.h"
#include "Components/PlayerBehaviourComponent.h"
#include "Persistence/TileMapTxtReader.h"
#include "Components/SpriteAnimationRendererComponent.h"
#include "Components/TileMapPositionComponent.h"
#include "Components/TileMovementComponent.h"

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
		SpriteRendererComponent* spriteRenderer = backgroundObject->AddComponent<SpriteRendererComponent>();
		spriteRenderer->SetDrawer(drawer);
		spriteRenderer->SetSprite("playfield.png");
	}

	{
		float halfSizeTileMapXf = ((float)tileMap->GetSizeX()) / 2.f;
		float halfSizeTileMapYf = ((float)tileMap->GetSizeY()) / 2.f;
		for (unsigned int x = 0; x < tileMap->GetSizeX(); ++x)
		{
			for (unsigned int y = 0; y < tileMap->GetSizeY(); ++y)
			{
				const Tile& tile = tileMap->GetTile(x, y);
				if (tile.type != TileType::Dot && tile.type != TileType::BigDot)
				{
					continue;
				}

				GameObject* smallDotObject = CreateGameObject();
				SpriteRendererComponent* spriteRenderer = smallDotObject->AddComponent<SpriteRendererComponent>();
				spriteRenderer->SetDrawer(drawer);
				spriteRenderer->SetSprite((tile.type == TileType::Dot) ? "Small_Dot_32.png" : "Big_Dot_32.png");
				TileMapPositionComponent* tileMapPosition = smallDotObject->AddComponent<TileMapPositionComponent>();
				tileMapPosition->SetTilePosition(x, y);
			}
		}
	}

	//player object
	{
		GameObject* playerObject = CreateGameObject();
		SpriteAnimationRendererComponent* spriteAnimationRenderer = playerObject->AddComponent<SpriteAnimationRendererComponent>();
		spriteAnimationRenderer->SetDrawer(drawer);
		spriteAnimationRenderer->SetFrames({ "open_32.png" , "closed_32.png" });
		spriteAnimationRenderer->SetSecondsBtwFrames(0.25f);
		TileMapPositionComponent* tileMapPosition = playerObject->AddComponent<TileMapPositionComponent>();
		tileMapPosition->SetTilePosition(13, 6);
		TileMovementComponent* tileMovement = playerObject->AddComponent<TileMovementComponent>();
		tileMovement->SetDestination(12, 6);
		PlayerBehaviourComponent* playerBehaviourComponent = playerObject->AddComponent<PlayerBehaviourComponent>();
		playerBehaviourComponent->SetSpeed(4.f);
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
	gameObjectsToDestroy.push_back(gameObject);
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
		delete gameObjectsToDestroy[i];
		gameObjectsToDestroy[i] = nullptr;
	}
	gameObjectsToDestroy.clear();
}
