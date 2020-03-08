#include "PlayerBehaviourComponent.h"
#include "GhostBehaviourComponent.h"
#include "../GameController.h"
#include "Renderer/SpriteAnimationComponent.h"
#include "TileMap/TileMapPositionComponent.h"
#include "TileMap/TileMovementComponent.h"
#include "TileMap/TeleportComponent.h"
#include "TileMap/DotComponent.h"

PlayerBehaviourComponent::PlayerBehaviourComponent()
{
	this->points = 0;
	this->lives = 2;
	this->animationRenderer = nullptr;
	this->tilePosition = nullptr;
	this->tileMovement = nullptr;
	this->speed = 1.f;
	this->teleportedTo = nullptr;
}

PlayerBehaviourComponent::~PlayerBehaviourComponent()
{
}

void PlayerBehaviourComponent::Start()
{
	this->animationRenderer = Owner->GetComponent<SpriteAnimationComponent>();
	this->tilePosition = Owner->GetComponent<TileMapPositionComponent>();
	this->tileMovement = Owner->GetComponent<TileMovementComponent>();
	//update the UI
	LivesValueUpdatedEventArgs livesValueUpdatedEventArgs;
	livesValueUpdatedEventArgs.lives = this->lives;
	LivesValueUpdatedEventDispatcher::Invoke(livesValueUpdatedEventArgs);
	PointsValueUpdatedEventArgs pointsUpdatedEventArgs;
	pointsUpdatedEventArgs.points = this->points;
	PointsValueUpdatedEventDispatcher::Invoke(pointsUpdatedEventArgs);
}

void PlayerBehaviourComponent::_Update(const float& deltaTime)
{
	if (!IsActive()) 
	{
		return;
	}

	const Vector2f kInput = GameController::Instance->GetInput();
	if (kInput.X > 0) 
	{
		tileMovement->MoveRight();
	}
	else if (kInput.X < 0) 
	{
		tileMovement->MoveLeft();
	}
	else if (kInput.Y > 0) 
	{
		tileMovement->MoveUp();
	}
	else if (kInput.Y < 0) 
	{
		tileMovement->MoveDown();
	}

	//update renderer	
	float rotation = 90.f * (float)tileMovement->GetMovementDirectionY();
	const int kMovementDirX = tileMovement->GetMovementDirectionX();
	const bool kFlipX = (kMovementDirX < 0);
	if (!kFlipX)
	{
		rotation *= -1;
	}
	this->animationRenderer->SetRotation(rotation);
	this->animationRenderer->SetFlip(kFlipX, false);	
}

void PlayerBehaviourComponent::SetSpeed(const float speed)
{
	this->speed = speed;
}

unsigned int PlayerBehaviourComponent::GetLives() const
{
	return this->lives;
}

unsigned int PlayerBehaviourComponent::GetPoints() const
{
	return this->points;
}

void PlayerBehaviourComponent::OnEvent(const CollisionEventArgs& event, const CollisionEventDispatcher& sender)
{
	switch (event.hit->Tag) 
	{
		case GameObjectTag::BigDot:
		{
			_BigDotCollected();
		}
		case GameObjectTag::Dot:
		{
			DotComponent* dot = event.hit->GetComponent<DotComponent>();
			_AddPoints(dot->GetPointsToAdd());
			//destroy the dot on the map
			GameController::Instance->Destroy(event.hit);
		}
		break;
		case GameObjectTag::Teleport:
		{
			if (event.status == CollisionStatus::Enter && teleportedTo == nullptr)
			{
				TeleportComponent* teleportComponent = event.hit->GetComponent<TeleportComponent>();
				TeleportComponent* linkedTeleportComponent = teleportComponent->GetLinkedTeleport();
				teleportedTo = linkedTeleportComponent;
				this->Owner->Position = linkedTeleportComponent->Owner->Position;
				const int kCurrX = (int)tilePosition->GetTilePositionX();
				const int kCurrY = (int)tilePosition->GetTilePositionY();
				const unsigned int kNextDestinationX = (unsigned int)(kCurrX + tileMovement->GetMovementDirectionX());
				const unsigned int kNextDestinationY = (unsigned int)(kCurrY + tileMovement->GetMovementDirectionY());
				tileMovement->SetDestination(kNextDestinationX, kNextDestinationY);
			}
			else if (event.status == CollisionStatus::Exit && event.hit == teleportedTo->Owner) 
			{
				teleportedTo = nullptr;
			}
		}
		break;
		case GameObjectTag::Ghost:
		{
			GhostBehaviourComponent* ghost = event.hit->GetComponent<GhostBehaviourComponent>();
			if (ghost->GetStatus() != GhostBehaviourComponent::GhostStatus::Dead)
			{
				if (ghost->GetStatus() == GhostBehaviourComponent::GhostStatus::Frightened)
				{

				}
				else 
				{
					_Death();
				}
			}			
		}
		break;
	}
}

void PlayerBehaviourComponent::_AddPoints(const unsigned int pointsToAdd)
{
	this->points += pointsToAdd;
	//invoke the event
	PointsValueUpdatedEventArgs pointsUpdatedEventArgs;
	pointsUpdatedEventArgs.points = this->points;
	PointsValueUpdatedEventDispatcher::Invoke(pointsUpdatedEventArgs);
}

void PlayerBehaviourComponent::_BigDotCollected()
{
	BigDotCollectedEventArgs bigDotCollectedEventArgs;
	BigDotCollectedEventDispatcher::Invoke(bigDotCollectedEventArgs);
}

void PlayerBehaviourComponent::_Death()
{
	this->lives -= 1;
	LivesValueUpdatedEventArgs livesValueUpdatedEventArgs;
	livesValueUpdatedEventArgs.lives = this->lives;
	LivesValueUpdatedEventDispatcher::Invoke(livesValueUpdatedEventArgs);
}
