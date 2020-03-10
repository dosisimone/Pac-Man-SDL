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
	this->SetDurationChangeState(3.0f);
}

void GameControllerComponent::Start()
{
	_LoadMap();
	_InstanceMapObjects();
	_InstanceUIObjects();
	_InstancePlayer();
	_InstanceGhosts();
}

void GameControllerComponent::SetDurationChangeState(const float duration)
{
	this->changeStateTimer.SetDuration(duration);
}

TileMap* GameControllerComponent::GetTileMap() const
{
	return this->tileMap;
}

void GameControllerComponent::OnEvent(const PlayerDeathEventArgs& event, const PlayerDeathEventDispatcher& sender)
{
	if (this->state != GameState::Playing) 
	{
		return;
	}

	if (lives == 0) 
	{
		_GameOver();
		return;
	}

	lives--;

	_ResetGame();	
}

void GameControllerComponent::OnEvent(const SimpleDotCollectedEventArgs& event, const SimpleDotCollectedEventDispatcher& sender)
{
	totDotsOnMap--;
	_AddPoints(10);

	if (totDotsOnMap == 0) 
	{
		_PlayerWin();
	}
}

void GameControllerComponent::OnEvent(const BigDotCollectedEventArgs& event, const BigDotCollectedEventDispatcher& sender)
{
	totDotsOnMap--;
	_AddPoints(50);

	if (totDotsOnMap == 0)
	{
		_PlayerWin();
	}
}

void GameControllerComponent::OnEvent(const GhostKilledEventArgs& event, const GhostKilledEventDispatcher& sender)
{
	_AddPoints(200);
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
			playerBehaviour->SetActive(true);

			int timerIndex = 0;
			for (GhostBehaviourComponent* ghostBehaviour : ghostBehaviours)
			{						
				ghostBehaviour->ForceTimer(5.f * timerIndex + 1.f);
				ghostBehaviour->SetActive(true);				
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
			tileMapPosition->SetTilePosition(x, y);
			switch (tile->type)
			{
			case TileType::Dot:
			{				
				tileObject->Tag = GameObjectTag::Dot;
				SpriteRendererComponent* spriteRenderer = tileObject->AddComponent<SpriteRendererComponent>();
				spriteRenderer->SetSprite("Small_Dot_32.png");
				totDotsOnMap++;
			}
			break;
			case TileType::BigDot:
			{
				tileObject->Tag = GameObjectTag::BigDot;
				SpriteRendererComponent* spriteRenderer = tileObject->AddComponent<SpriteRendererComponent>();
				spriteRenderer->SetSprite("Big_Dot_32.png");
				totDotsOnMap++;
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
	this->playerBehaviour = playerObject->AddComponent<PlayerBehaviourComponent>();
	this->playerBehaviour->SetActive(false);
	//subscribe to player events
	this->playerBehaviour->Subscribe((PlayerDeathEventListener*)this);
	this->playerBehaviour->Subscribe((SimpleDotCollectedEventListener*)this);
	this->playerBehaviour->Subscribe((BigDotCollectedEventListener*)this);
	this->playerBehaviour->Subscribe((GhostKilledEventListener*)this);
}

void GameControllerComponent::_InstanceGhosts()
{
	//red ghost
	{
		GameObject* ghostObject = GameController::Instance->CreateGameObject();
		ghostObject->Tag = GameObjectTag::Ghost;
		RedGhostBehaviourComponent* redGhostBehaviourComponent = ghostObject->AddComponent<RedGhostBehaviourComponent>();
		ghostBehaviours.push_back(redGhostBehaviourComponent);
	}
	//blue ghost
	{
		GameObject* ghostObject = GameController::Instance->CreateGameObject();
		ghostObject->Tag = GameObjectTag::Ghost;
		BlueGhostBehaviourComponent* blueGhostBehaviourComponent = ghostObject->AddComponent<BlueGhostBehaviourComponent>();
		ghostBehaviours.push_back(blueGhostBehaviourComponent);
	}
	//pink ghost
	{
		GameObject* ghostObject = GameController::Instance->CreateGameObject();
		ghostObject->Tag = GameObjectTag::Ghost;
		PinkGhostBehaviourComponent* pinkGhostBehaviourComponent = ghostObject->AddComponent<PinkGhostBehaviourComponent>();
		ghostBehaviours.push_back(pinkGhostBehaviourComponent);
	}
	//orange ghost
	{
		GameObject* ghostObject = GameController::Instance->CreateGameObject();
		ghostObject->Tag = GameObjectTag::Ghost;
		OrangeGhostBehaviourComponent* orangeGhostBehaviourComponent = ghostObject->AddComponent<OrangeGhostBehaviourComponent>();
		ghostBehaviours.push_back(orangeGhostBehaviourComponent);
	}

	for (GhostBehaviourComponent* ghostBehaviour : ghostBehaviours) 
	{
		ghostBehaviour->SetActive(false);
	}
}

void GameControllerComponent::_GameOver()
{
	this->state = GameState::GameOver;

	std::vector<GameObject*> allGameObjects = GameController::Instance->GetAllGameObjects();
	for (GameObject* obj : allGameObjects) 
	{
		GameController::Instance->Destroy(obj);
	}

	GameObject* scoreLabelTextUIObject = GameController::Instance->CreateGameObject();
	scoreLabelTextUIObject->Tag = GameObjectTag::UI;
	UITextComponent* scoreLabelTextUIComponent = scoreLabelTextUIObject->AddComponent<UITextComponent>();
	scoreLabelTextUIComponent->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	scoreLabelTextUIComponent->SetScreenPosition(20, 50);
	scoreLabelTextUIComponent->SetText("GAME OVER");
}

void GameControllerComponent::_PlayerWin()
{
	this->state = GameState::GameOver;

	std::vector<GameObject*> allGameObjects = GameController::Instance->GetAllGameObjects();
	for (GameObject* obj : allGameObjects)
	{
		GameController::Instance->Destroy(obj);
	}

	GameObject* scoreLabelTextUIObject = GameController::Instance->CreateGameObject();
	scoreLabelTextUIObject->Tag = GameObjectTag::UI;
	UITextComponent* scoreLabelTextUIComponent = scoreLabelTextUIObject->AddComponent<UITextComponent>();
	scoreLabelTextUIComponent->SetFont("freefont-ttf\\sfd\\FreeMonoBold.ttf");
	scoreLabelTextUIComponent->SetScreenPosition(20, 50);
	scoreLabelTextUIComponent->SetText("PLAYER WIN!");
}

void GameControllerComponent::_ResetGame()
{
	this->state = GameState::Paused;
	changeStateTimer.Reset();	

	for (GhostBehaviourComponent* ghost : ghostBehaviours)
	{
		GameController::Instance->Destroy(ghost->GetOwner());
	}
	ghostBehaviours.clear();

	GameController::Instance->Destroy(playerBehaviour->GetOwner());	

	_InstancePlayer();
	_InstanceGhosts();

	//setup UI
	LivesValueUpdatedEventArgs livesValueUpdatedEventArgs;
	livesValueUpdatedEventArgs.lives = lives;
	LivesValueUpdatedEventDispatcher::Invoke(livesValueUpdatedEventArgs);
}

void GameControllerComponent::_AddPoints(const unsigned int pointsToAdd)
{
	points += pointsToAdd;
	PointsValueUpdatedEventArgs pointsValueUpdatedEventArgs;
	pointsValueUpdatedEventArgs.points = points;
	PointsValueUpdatedEventDispatcher::Invoke(pointsValueUpdatedEventArgs);
}
