#include "GameControllerComponent.h"
#include "../GameObject.h"
#include "../TileMap.h"
#include "../Persistence/TileMapTxtReader.h"
#include "../GameController.h"
#include "Renderer/SpriteRendererComponent.h"
#include "Renderer/SpriteAnimationComponent.h"
#include "TileMap/TileMapPositionComponent.h"
#include "TileMap/TileMovementComponent.h"
#include "TileMap/TeleportComponent.h"
#include "TileMap/DotComponent.h"
#include "PlayerBehaviourComponent.h"
#include "GhostBehaviourComponent.h"
#include "Collider/CollisionComponent.h"

GameControllerComponent::GameControllerComponent()
{
	this->state = GameState::Paused;
	this->playerBehaviour = nullptr;
}

GameControllerComponent::~GameControllerComponent()
{
	delete tileMap;
	tileMap = nullptr;
}

void GameControllerComponent::Start()
{
	_LoadMap();
	_InstanceMapObjects();
	_InstanceUIObjects();
	_InstancePlayer();


	playerBehaviour = GameController::Instance->GetComponent<PlayerBehaviourComponent>();
	playerBehaviour->GetOwner()->SetActive(false);

	ghostBehaviours  = GameController::Instance->GetComponents<GhostBehaviourComponent>();
	for (GhostBehaviourComponent* ghostBehaviour : ghostBehaviours)
	{		
		ghostBehaviour->GetOwner()->SetActive(false);
	}
}

void GameControllerComponent::SetDurationChangeState(const float duration)
{
	this->changeStateTimer.SetDuration(duration);
}

TileMap* GameControllerComponent::GetTileMap() const
{
	return this->tileMap;
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

			playerBehaviour->GetOwner()->SetActive(true);

			for (GhostBehaviourComponent* ghostBehaviour : ghostBehaviours)
			{
				ghostBehaviour->GetOwner()->SetActive(true);
			}




		}
	}
	break;
	}
}

void GameControllerComponent::_LoadMap()
{
	TileMapTxtReader mapTxtReader;
	tileMap = mapTxtReader.Read("map.txt");
	tileMap->SetDistanceBtwTiles(0.5f);
}

void GameControllerComponent::_InstanceMapObjects()
{
	// background
	GameObject* backgroundObject = GameController::Instance->CreateGameObject();
	backgroundObject->Tag = GameObjectTag::Background;
	SpriteRendererComponent* spriteRenderer = backgroundObject->AddComponent<SpriteRendererComponent>();
	spriteRenderer->SetSprite("playfield.png");
	// map
	TeleportComponent* firstTeleport = nullptr;
	TeleportComponent* previousTeleport = nullptr;
	for (unsigned int x = 0; x < tileMap->GetSizeX(); ++x)
	{
		for (unsigned int y = 0; y < tileMap->GetSizeY(); ++y)
		{
			const Tile& tile = tileMap->GetTile(x, y);
			if (!tile.isWalkable)
			{
				continue;
			}

			GameObject* tileObject = GameController::Instance->CreateGameObject();
			TileMapPositionComponent* tileMapPosition = tileObject->AddComponent<TileMapPositionComponent>();
			tileMapPosition->SetTileMap(this->GetTileMap());
			tileMapPosition->SetTilePosition(x, y);
			switch (tile.type)
			{
			case TileType::Dot:
			{
				tileObject->Tag = GameObjectTag::Dot;
				SpriteRendererComponent* spriteRenderer = tileObject->AddComponent<SpriteRendererComponent>();
				spriteRenderer->SetSprite("Small_Dot_32.png");
				DotComponent* dot = tileObject->AddComponent<DotComponent>();
				dot->SetPointsToAdd(10);
			}
			break;
			case TileType::BigDot:
			{
				tileObject->Tag = GameObjectTag::BigDot;
				SpriteRendererComponent* spriteRenderer = tileObject->AddComponent<SpriteRendererComponent>();
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
		}
	}

	if (firstTeleport != nullptr && previousTeleport != nullptr && firstTeleport != previousTeleport)
	{
		previousTeleport->SetLinkedTeleport(firstTeleport);
	}
}

void GameControllerComponent::_InstanceUIObjects()
{

}

void GameControllerComponent::_InstancePlayer()
{
	GameObject* playerObject = GameController::Instance->CreateGameObject();
	playerObject->Tag = GameObjectTag::Player;
	SpriteRendererComponent* spriteRenderer = playerObject->AddComponent<SpriteRendererComponent>();
	SpriteAnimationComponent* spriteAnimationRenderer = playerObject->AddComponent<SpriteAnimationComponent>();
	TileMapPositionComponent* tileMapPosition = playerObject->AddComponent<TileMapPositionComponent>();
	tileMapPosition->SetTileMap(this->GetTileMap());
	tileMapPosition->SetTilePosition(14, 7);
	TileMovementComponent* tileMovement = playerObject->AddComponent<TileMovementComponent>();
	tileMovement->MoveLeft();
	tileMovement->SetSpeed(4.f);
	CollisionComponent* collisionComponent = playerObject->AddComponent<CollisionComponent>();
	PlayerBehaviourComponent* playerBehaviourComponent = playerObject->AddComponent<PlayerBehaviourComponent>();
}

void GameControllerComponent::_InstanceGhosts()
{
	GameObject* ghost1Object = GameController::Instance->CreateGameObject();
	ghost1Object->Tag = GameObjectTag::Ghost;
	SpriteRendererComponent* spriteRenderer = ghost1Object->AddComponent<SpriteRendererComponent>();
	SpriteAnimationComponent* spriteAnimationRenderer = ghost1Object->AddComponent<SpriteAnimationComponent>();
	TileMapPositionComponent* tileMapPosition = ghost1Object->AddComponent<TileMapPositionComponent>();
	tileMapPosition->SetTileMap(this->GetTileMap());
	tileMapPosition->SetTilePosition(21, 20);
	TileMovementComponent* tileMovement = ghost1Object->AddComponent<TileMovementComponent>();
	tileMovement->MoveDown();
	tileMovement->SetSpeed(3.f);
	GhostBehaviourComponent* ghost1BehaviourComponent = ghost1Object->AddComponent<GhostBehaviourComponent>();
}
