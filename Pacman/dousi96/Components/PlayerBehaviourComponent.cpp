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
	this->oldValidInput = Vector2f::LEFT;
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

void PlayerBehaviourComponent::Update(const float deltaTime)
{
	if (tileMovement->IsAtDestination()) 
	{
		const Vector2f kInput = GameController::Instance->GetInput();
		const unsigned int kCurrX = tileMovement->GetCurrentTileX();
		const unsigned int kCurrY = tileMovement->GetCurrentTileY();
		unsigned int nextDestinationX = (unsigned int)((int)kCurrX + (int)kInput.X);
		unsigned int nextDestinationY = (unsigned int)((int)kCurrY + (int)kInput.Y);

		if (!tileMovement->SetDestination(nextDestinationX, nextDestinationY) 
			|| kInput.Length() == 0.f)
		{
			nextDestinationX = (unsigned int)((int)kCurrX + (int)oldValidInput.X);
			nextDestinationY = (unsigned int)((int)kCurrY + (int)oldValidInput.Y);
			tileMovement->SetDestination(nextDestinationX, nextDestinationY);
		}
		else 
		{
			oldValidInput = kInput;
		}
	}

	unsigned int destX = tileMovement->GetDestinationTileX();
	unsigned int destY = tileMovement->GetDestinationTileY();
	Vector2f destination = tilePosition->GetTileWorldPosition(destX, destY);
	Vector2f direction = destination - Owner->Position;

	const float kMoveDelta = deltaTime * speed;
	if (direction.Length() < kMoveDelta) 
	{
		unsigned int currX = tileMovement->GetDestinationTileX();
		unsigned int currY = tileMovement->GetDestinationTileY();
		tileMovement->SetCurrentTile(currX, currY);
		Owner->Position = destination;
	}
	else 
	{
		//update position
		direction.Normalize();
		Owner->Position += direction * kMoveDelta;
	}	

	//update renderer	
	float rotation = 0.f;
	if (oldValidInput.Y < 0.f)
	{
		rotation = 90.f;
	}
	else if (oldValidInput.Y > 0.f)
	{
		rotation = -90.f;
	}
	this->animationRenderer->SetRotation(rotation);

	bool flipX = (oldValidInput.X < 0.f);
	if (!flipX)
	{
		rotation *= -1;
	}
	this->animationRenderer->SetFlip(flipX, false);	
}

void PlayerBehaviourComponent::SetSpeed(const float speed)
{
	this->speed = speed;
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
				const unsigned int kCurrX = tilePosition->GetTilePositionX();
				const unsigned int kCurrY = tilePosition->GetTilePositionY();
				const unsigned int kNextDestinationX = (unsigned int)((int)kCurrX + (int)oldValidInput.X);
				const unsigned int kNextDestinationY = (unsigned int)((int)kCurrY + (int)oldValidInput.Y);
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
