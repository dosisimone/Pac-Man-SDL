#include "TileMovementComponent.h"
#include "TileMapPositionComponent.h"
#include "../../TileMap.h"
#include "../../GameController.h"
#include "../../GameObject.h"
#include "../GameControllerComponent.h"

TileMovementComponent::TileMovementComponent()
{
	this->currTilePositionX = 0;
	this->currTilePositionY = 0;
	this->destTilePositionX = 0;
	this->destTilePositionY = 0;
	this->speed = 1.0f;
	this->tileMapPositionComponent = nullptr;
}

TileMovementComponent::~TileMovementComponent()
{
}

void TileMovementComponent::Awake()
{
	this->tileMapPositionComponent = GetOwner()->GetOrAddComponent<TileMapPositionComponent>();
}

void TileMovementComponent::Start()
{
	this->currTilePositionX = this->tileMapPositionComponent->GetTilePositionX();
	this->currTilePositionY = this->tileMapPositionComponent->GetTilePositionY();
	this->destTilePositionX = this->tileMapPositionComponent->GetTilePositionX();
	this->destTilePositionY = this->tileMapPositionComponent->GetTilePositionY();
}

void TileMovementComponent::SetSpeed(const float& speed)
{
	this->speed = speed;
}

unsigned int TileMovementComponent::GetCurrentTileX() const
{
	return this->currTilePositionX;
}

unsigned int TileMovementComponent::GetCurrentTileY() const
{
	return this->currTilePositionY;
}

void TileMovementComponent::SetCurrentTile(const unsigned int x, const unsigned int y)
{
	if (!this->tileMapPositionComponent->GetTileMap()->AreCoordsValid(x, y))
	{
		return;
	}
	this->currTilePositionX = x;
	this->currTilePositionY = y;
	this->destTilePositionX = x;
	this->destTilePositionY = y;
	this->tileMapPositionComponent->SetTilePosition(x, y);
}

unsigned int TileMovementComponent::GetDestinationTileX() const
{
	return this->destTilePositionX;
}

unsigned int TileMovementComponent::GetDestinationTileY() const
{
	return this->destTilePositionY;
}

bool TileMovementComponent::SetDestination(const unsigned int x, const unsigned int y)
{
	if (!this->tileMapPositionComponent->GetTileMap()->AreCoordsValid(x, y))
	{
		return false;
	}
	this->destTilePositionX = x;
	this->destTilePositionY = y;
	return true;
}

int TileMovementComponent::GetMovementDirectionX() const
{
	return (int)GetDestinationTileX() - (int)GetCurrentTileX();
}

int TileMovementComponent::GetMovementDirectionY() const
{
	return (int)GetDestinationTileY() - (int)GetCurrentTileY();
}

bool TileMovementComponent::IsAtDestination() const
{
	return (GetDestinationTileX() == GetCurrentTileX() && GetDestinationTileY() == GetCurrentTileY());
}

void TileMovementComponent::_Update(const float& deltaTime)
{	
	const unsigned int kOldDestinationTileX = GetDestinationTileX();
	const unsigned int kOldDestinationTileY = GetDestinationTileY();
	Vector2f destination = this->tileMapPositionComponent->GetTileMap()->GetTileWorldPosition(kOldDestinationTileX, kOldDestinationTileY);
	Vector2f distance = destination - GetOwner()->Position;

	const float kMoveDelta = deltaTime * speed;
	if (kMoveDelta > distance.Length())
	{
		// arrived at destination
		SetCurrentTile(kOldDestinationTileX, kOldDestinationTileY);
	}
	else
	{
		//update position
		distance.Normalize();
		GetOwner()->Position += distance * kMoveDelta;
	}
}
