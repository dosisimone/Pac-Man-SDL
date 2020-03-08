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
	this->inputX = 0;
	this->inputY = 0;
	this->directionX = 0;
	this->directionY = 0;
	this->tileMapPositionComponent = nullptr;
}

TileMovementComponent::~TileMovementComponent()
{
}

void TileMovementComponent::Awake()
{
	this->tileMapPositionComponent = GetOwner()->GetComponent<TileMapPositionComponent>();
	this->currTilePositionX = this->tileMapPositionComponent->GetTilePositionX();
	this->currTilePositionY = this->tileMapPositionComponent->GetTilePositionY();
	this->destTilePositionX = this->tileMapPositionComponent->GetTilePositionX();
	this->destTilePositionY = this->tileMapPositionComponent->GetTilePositionY();
}

void TileMovementComponent::MoveUp()
{
	if (_IsTileWalkable(GetDestinationTileX(), GetDestinationTileY() + 1))
	{
		inputX = +0;
		inputY = +1;		
	}
}

void TileMovementComponent::MoveDown()
{
	if (_IsTileWalkable(GetDestinationTileX(), GetDestinationTileY() - 1))
	{
		inputX = +0;
		inputY = -1;
	}
}

void TileMovementComponent::MoveRight()
{
	if (_IsTileWalkable(GetDestinationTileX() + 1, GetDestinationTileY()))
	{
		inputX = +1;
		inputY = +0;
	}
}

void TileMovementComponent::MoveLeft()
{
	if (_IsTileWalkable(GetDestinationTileX() - 1, GetDestinationTileY()))
	{
		inputX = -1;
		inputY = +0;
	}
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
	if (_IsTileWalkable(x, y)) 
	{
		this->currTilePositionX = x;
		this->currTilePositionY = y;
	}
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
	if (_IsTileWalkable(x, y))
	{
		this->destTilePositionX = x;
		this->destTilePositionY = y;
		return true;
	}
	return false;
}

int TileMovementComponent::GetMovementDirectionX() const
{
	return this->directionX;
}

int TileMovementComponent::GetMovementDirectionY() const
{
	return this->directionY;
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
		GetOwner()->Position = destination;
		const bool kInputIsNull = (inputX == 0 && inputY == 0);
		if (!SetDestination(kOldDestinationTileX + inputX, kOldDestinationTileY + inputY) || kInputIsNull)
		{					
			const int kOldDirectionX = GetMovementDirectionX();
			const int kOldDirectionY = GetMovementDirectionY();
			SetDestination(kOldDestinationTileX + kOldDirectionX, kOldDestinationTileY + kOldDirectionY);			
		}	
		else 
		{
			_SetMovementDirection(inputX, inputY);
		}
		SetCurrentTile(kOldDestinationTileX, kOldDestinationTileY);
	}
	else
	{
		//update position
		distance.Normalize();
		GetOwner()->Position += distance * kMoveDelta;
	}
}

void TileMovementComponent::_SetMovementDirection(const int x, const int y)
{
	this->directionX = x;
	this->directionY = y;
}

bool TileMovementComponent::_IsTileWalkable(const unsigned int x, const unsigned int y) const
{
	if (x >= this->tileMapPositionComponent->GetTileMap()->GetSizeX())
	{
		return false;
	}
	if (y >= this->tileMapPositionComponent->GetTileMap()->GetSizeY())
	{
		return false;
	}
	const Tile& tile = this->tileMapPositionComponent->GetTileMap()->GetTile(x, y);
	return tile.isWalkable;
}
