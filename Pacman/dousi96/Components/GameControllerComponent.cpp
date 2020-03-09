#include "GameControllerComponent.h"
#include "../GameObject.h"
#include "../TileMap.h"
#include "../Persistence/TileMapTxtReader.h"
#include "../GameController.h"
#include "Renderer/SpriteRendererComponent.h"
#include "Renderer/SpriteAnimationComponent.h"
#include "TileMap/TileMapPositionComponent.h"
#include "TileMap/TileMovementComponent.h"
#include "TileMap/GhostPathfinderComponent.h"
#include "TileMap/TeleportComponent.h"
#include "TileMap/DotComponent.h"
#include "PlayerBehaviourComponent.h"
#include "GhostBehaviourComponent.h"
#include "Collider/CollisionComponent.h"
#include "UI/UITextComponent.h"
#include "UI/UILivesLabelComponent.h"
#include "UI/UIPointsLabelComponent.h"

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

void GameControllerComponent::Awake()
{
	this->SetDurationChangeState(0.0f);
}

void GameControllerComponent::Start()
{
	_LoadMap();
	_InstanceMapObjects();
	_InstanceUIObjects();
	_InstancePlayer();
	_InstanceGhosts();

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

	if (changeStateTimer.Check())
	{
		changeStateTimer.Reset();

		switch (this->state)
		{
		case GameState::Paused:
		{
			this->state = GameState::Playing;

			playerBehaviour->GetOwner()->SetActive(true);

			int timerIndex = 0;
			for (GhostBehaviourComponent* ghostBehaviour : ghostBehaviours)
			{				
				ghostBehaviour->ForceTimer(3.f * timerIndex + 1.f);
				ghostBehaviour->GetOwner()->SetActive(true);
				timerIndex++;
			}




		}
		break;
	}
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
			Tile* tile = tileMap->GetTile(x, y);
			if (!tile->isPlayerWalkable)
			{
				continue;
			}

			GameObject* tileObject = GameController::Instance->CreateGameObject();
			TileMapPositionComponent* tileMapPosition = tileObject->AddComponent<TileMapPositionComponent>();
			tileMapPosition->SetTileMap(this->GetTileMap());
			tileMapPosition->SetTilePosition(x, y);
			switch (tile->type)
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
	GameObject* scoreLabelTextUIObject = GameController::Instance->CreateGameObject();
	scoreLabelTextUIObject->Tag = GameObjectTag::UI;
	UITextComponent* scoreLabelTextUIComponent = scoreLabelTextUIObject->AddComponent<UITextComponent>();
	scoreLabelTextUIComponent->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	scoreLabelTextUIComponent->SetScreenPosition(20, 50);
	scoreLabelTextUIComponent->SetText("Score: ");

	GameObject* scoreLabelValueUIObject = GameController::Instance->CreateGameObject();
	scoreLabelValueUIObject->Tag = GameObjectTag::UI;
	UITextComponent* scoreLabelValueUIComponent = scoreLabelValueUIObject->AddComponent<UITextComponent>();
	scoreLabelValueUIComponent->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	scoreLabelValueUIComponent->SetScreenPosition(110, 50);
	scoreLabelValueUIComponent->SetText("0");
	UIPointsLabelComponent* pointsLabelUIComponent = scoreLabelValueUIObject->AddComponent<UIPointsLabelComponent>();

	GameObject* livesLabelTextUIObject = GameController::Instance->CreateGameObject();
	livesLabelTextUIObject->Tag = GameObjectTag::UI;
	UITextComponent* livesLabelTextUIComponent = livesLabelTextUIObject->AddComponent<UITextComponent>();
	livesLabelTextUIComponent->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	livesLabelTextUIComponent->SetScreenPosition(20, 90);
	livesLabelTextUIComponent->SetText("Lives: ");

	GameObject* livesLabelValueUIObject = GameController::Instance->CreateGameObject();
	livesLabelValueUIObject->Tag = GameObjectTag::UI;
	UITextComponent* livesLabelValueUIComponent = livesLabelValueUIObject->AddComponent<UITextComponent>();
	livesLabelValueUIComponent->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	livesLabelValueUIComponent->SetScreenPosition(110, 90);
	livesLabelValueUIComponent->SetText("2");
	UILivesLabelComponent* livesLabelUIComponent = livesLabelValueUIObject->AddComponent<UILivesLabelComponent>();
}

void GameControllerComponent::_InstancePlayer()
{
	GameObject* playerObject = GameController::Instance->CreateGameObject();
	playerObject->Tag = GameObjectTag::Player;
	SpriteRendererComponent* spriteRenderer = playerObject->AddComponent<SpriteRendererComponent>();
	SpriteAnimationComponent* spriteAnimationRenderer = playerObject->AddComponent<SpriteAnimationComponent>();
	SpriteAnimationComponent::Animation defaultPlayerAnimation;
	defaultPlayerAnimation.name = "default";
	defaultPlayerAnimation.sprites = { "open_32.png" , "closed_32.png" };
	defaultPlayerAnimation.secondsBtwFrames = 0.25f;
	spriteAnimationRenderer->AddAnimation(defaultPlayerAnimation);

	TileMapPositionComponent* tileMapPosition = playerObject->AddComponent<TileMapPositionComponent>();
	tileMapPosition->SetTileMap(this->GetTileMap());
	tileMapPosition->SetTilePosition(14, 7);
	TileMovementComponent* tileMovement = playerObject->AddComponent<TileMovementComponent>();
	tileMovement->SetSpeed(4.f);
	CollisionComponent* collisionComponent = playerObject->AddComponent<CollisionComponent>();
	PlayerBehaviourComponent* playerBehaviourComponent = playerObject->AddComponent<PlayerBehaviourComponent>();
}

void GameControllerComponent::_InstanceGhosts()
{
	//ghost 1
	{
		GameObject* ghostObject = GameController::Instance->CreateGameObject();
		ghostObject->Tag = GameObjectTag::Ghost;
		// rendering
		SpriteRendererComponent* spriteRenderer = ghostObject->AddComponent<SpriteRendererComponent>();
		SpriteAnimationComponent* spriteAnimationRenderer = ghostObject->AddComponent<SpriteAnimationComponent>();
		SpriteAnimationComponent::Animation defaultGhostAnimation;
		defaultGhostAnimation.name = "default";
		defaultGhostAnimation.sprites = { "ghost_32_red.png" };
		defaultGhostAnimation.secondsBtwFrames = 60.f;
		SpriteAnimationComponent::Animation deadGhostAnimation;
		deadGhostAnimation.name = "dead";
		deadGhostAnimation.sprites = { "Ghost_Dead_32.png" };
		deadGhostAnimation.secondsBtwFrames = 60.f;
		SpriteAnimationComponent::Animation frightenedGhostAnimation;
		frightenedGhostAnimation.name = "frightened";
		frightenedGhostAnimation.sprites = { "Ghost_Vulnerable_32.png" };
		frightenedGhostAnimation.secondsBtwFrames = 60.f;
		spriteAnimationRenderer->AddAnimation(defaultGhostAnimation);
		spriteAnimationRenderer->AddAnimation(deadGhostAnimation);
		spriteAnimationRenderer->AddAnimation(frightenedGhostAnimation);
		// tilemap position & movement
		TileMapPositionComponent* tileMapPosition = ghostObject->AddComponent<TileMapPositionComponent>();
		tileMapPosition->SetTileMap(this->GetTileMap());
		TileMovementComponent* tileMovement = ghostObject->AddComponent<TileMovementComponent>();
		tileMovement->SetSpeed(3.f);
		GhostPathfinderComponent* tileMapPathfinder = ghostObject->AddComponent<GhostPathfinderComponent>();
		GhostBehaviourComponent* ghostBehaviourComponent = ghostObject->AddComponent<GhostBehaviourComponent>();
		ghostBehaviourComponent->SetGhostHouseTile(12, 16);
		ghostBehaviourComponent->SetScatterStatusTarget(27, 30);
		ghostBehaviours.push_back(ghostBehaviourComponent);
	}
	//ghost 2
	{
		GameObject* ghostObject = GameController::Instance->CreateGameObject();
		ghostObject->Tag = GameObjectTag::Ghost;
		// rendering
		SpriteRendererComponent* spriteRenderer = ghostObject->AddComponent<SpriteRendererComponent>();
		SpriteAnimationComponent* spriteAnimationRenderer = ghostObject->AddComponent<SpriteAnimationComponent>();
		SpriteAnimationComponent::Animation defaultGhostAnimation;
		defaultGhostAnimation.name = "default";
		defaultGhostAnimation.sprites = { "ghost_32_cyan.png" };
		defaultGhostAnimation.secondsBtwFrames = 60.f;
		SpriteAnimationComponent::Animation deadGhostAnimation;
		deadGhostAnimation.name = "dead";
		deadGhostAnimation.sprites = { "Ghost_Dead_32.png" };
		deadGhostAnimation.secondsBtwFrames = 60.f;
		SpriteAnimationComponent::Animation frightenedGhostAnimation;
		frightenedGhostAnimation.name = "frightened";
		frightenedGhostAnimation.sprites = { "Ghost_Vulnerable_32.png" };
		frightenedGhostAnimation.secondsBtwFrames = 60.f;
		spriteAnimationRenderer->AddAnimation(defaultGhostAnimation);
		spriteAnimationRenderer->AddAnimation(deadGhostAnimation);
		spriteAnimationRenderer->AddAnimation(frightenedGhostAnimation);
		// tilemap position & movement
		TileMapPositionComponent* tileMapPosition = ghostObject->AddComponent<TileMapPositionComponent>();
		tileMapPosition->SetTileMap(this->GetTileMap());
		TileMovementComponent* tileMovement = ghostObject->AddComponent<TileMovementComponent>();
		tileMovement->SetSpeed(3.f);
		GhostPathfinderComponent* tileMapPathfinder = ghostObject->AddComponent<GhostPathfinderComponent>();
		GhostBehaviourComponent* ghostBehaviourComponent = ghostObject->AddComponent<GhostBehaviourComponent>();
		ghostBehaviourComponent->SetGhostHouseTile(13, 16);
		ghostBehaviourComponent->SetScatterStatusTarget(0, 30);
		ghostBehaviours.push_back(ghostBehaviourComponent);
	}
	//ghost 3
	{
		GameObject* ghostObject = GameController::Instance->CreateGameObject();
		ghostObject->Tag = GameObjectTag::Ghost;
		// rendering
		SpriteRendererComponent* spriteRenderer = ghostObject->AddComponent<SpriteRendererComponent>();
		SpriteAnimationComponent* spriteAnimationRenderer = ghostObject->AddComponent<SpriteAnimationComponent>();
		SpriteAnimationComponent::Animation defaultGhostAnimation;
		defaultGhostAnimation.name = "default";
		defaultGhostAnimation.sprites = { "ghost_32_pink.png" };
		defaultGhostAnimation.secondsBtwFrames = 60.f;
		SpriteAnimationComponent::Animation deadGhostAnimation;
		deadGhostAnimation.name = "dead";
		deadGhostAnimation.sprites = { "Ghost_Dead_32.png" };
		deadGhostAnimation.secondsBtwFrames = 60.f;
		SpriteAnimationComponent::Animation frightenedGhostAnimation;
		frightenedGhostAnimation.name = "frightened";
		frightenedGhostAnimation.sprites = { "Ghost_Vulnerable_32.png" };
		frightenedGhostAnimation.secondsBtwFrames = 60.f;
		spriteAnimationRenderer->AddAnimation(defaultGhostAnimation);
		spriteAnimationRenderer->AddAnimation(deadGhostAnimation);
		spriteAnimationRenderer->AddAnimation(frightenedGhostAnimation);
		// tilemap position & movement
		TileMapPositionComponent* tileMapPosition = ghostObject->AddComponent<TileMapPositionComponent>();
		tileMapPosition->SetTileMap(this->GetTileMap());
		TileMovementComponent* tileMovement = ghostObject->AddComponent<TileMovementComponent>();
		tileMovement->SetSpeed(3.f);
		GhostPathfinderComponent* tileMapPathfinder = ghostObject->AddComponent<GhostPathfinderComponent>();
		GhostBehaviourComponent* ghostBehaviourComponent = ghostObject->AddComponent<GhostBehaviourComponent>();
		ghostBehaviourComponent->SetGhostHouseTile(14, 16);
		ghostBehaviourComponent->SetScatterStatusTarget(0, 0);
		ghostBehaviours.push_back(ghostBehaviourComponent);
	}
	//ghost 4
	{
		GameObject* ghostObject = GameController::Instance->CreateGameObject();
		ghostObject->Tag = GameObjectTag::Ghost;
		// rendering
		SpriteRendererComponent* spriteRenderer = ghostObject->AddComponent<SpriteRendererComponent>();
		SpriteAnimationComponent* spriteAnimationRenderer = ghostObject->AddComponent<SpriteAnimationComponent>();
		SpriteAnimationComponent::Animation defaultGhostAnimation;
		defaultGhostAnimation.name = "default";
		defaultGhostAnimation.sprites = { "ghost_32_orange.png" };
		defaultGhostAnimation.secondsBtwFrames = 60.f;
		SpriteAnimationComponent::Animation deadGhostAnimation;
		deadGhostAnimation.name = "dead";
		deadGhostAnimation.sprites = { "Ghost_Dead_32.png" };
		deadGhostAnimation.secondsBtwFrames = 60.f;
		SpriteAnimationComponent::Animation frightenedGhostAnimation;
		frightenedGhostAnimation.name = "frightened";
		frightenedGhostAnimation.sprites = { "Ghost_Vulnerable_32.png" };
		frightenedGhostAnimation.secondsBtwFrames = 60.f;
		spriteAnimationRenderer->AddAnimation(defaultGhostAnimation);
		spriteAnimationRenderer->AddAnimation(deadGhostAnimation);
		spriteAnimationRenderer->AddAnimation(frightenedGhostAnimation);
		// tilemap position & movement
		TileMapPositionComponent* tileMapPosition = ghostObject->AddComponent<TileMapPositionComponent>();
		tileMapPosition->SetTileMap(this->GetTileMap());
		TileMovementComponent* tileMovement = ghostObject->AddComponent<TileMovementComponent>();
		tileMovement->SetSpeed(3.f);
		GhostPathfinderComponent* tileMapPathfinder = ghostObject->AddComponent<GhostPathfinderComponent>();
		GhostBehaviourComponent* ghostBehaviourComponent = ghostObject->AddComponent<GhostBehaviourComponent>();
		ghostBehaviourComponent->SetGhostHouseTile(15, 16);
		ghostBehaviourComponent->SetScatterStatusTarget(27, 0);
		ghostBehaviours.push_back(ghostBehaviourComponent);
	}
}
