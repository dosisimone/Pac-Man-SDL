#include "TileMovementComponent.h"
#include "TileMapPositionComponent.h"
#include "../TileMap.h"
#include "../GameController.h"

TileMovementComponent::TileMovementComponent()
{
	this->currTilePositionX = 0;
	this->currTilePositionY = 0;
	this->destTilePositionX = 0;
	this->destTilePositionY = 0;
	this->tileMap = nullptr;
	this->tileMapPositionComponent = nullptr;
}

TileMovementComponent::~TileMovementComponent()
{
}

void TileMovementComponent::Start()
{
	this->tileMap = GameController::Instance->GetTileMap();
	this->tileMapPositionComponent = Owner->GetComponent<TileMapPositionComponent>();
	this->currTilePositionX = this->tileMapPositionComponent->GetTilePositionX();
	this->currTilePositionY = this->tileMapPositionComponent->GetTilePositionY();
	this->destTilePositionX = this->tileMapPositionComponent->GetTilePositionX();
	this->destTilePositionY = this->tileMapPositionComponent->GetTilePositionY();	
}

bool TileMovementComponent::IsAtDestination() const
{
	return this->currTilePositionX == this->destTilePositionX 
		&& this->currTilePositionY == this->destTilePositionY;
}

void TileMovementComponent::SetCurrentTile(const unsigned int x, const unsigned int y)
{
	if (_IsTileWalkable(x, y)) 
	{
		this->currTilePositionX = x;
		this->currTilePositionY = y;
	}
}

unsigned int TileMovementComponent::GetCurrentTileX() const
{
	return this->currTilePositionX;
}

unsigned int TileMovementComponent::GetCurrentTileY() const
{
	return this->currTilePositionY;
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

unsigned int TileMovementComponent::GetDestinationTileX() const
{
	return this->destTilePositionX;
}

unsigned int TileMovementComponent::GetDestinationTileY() const
{
	return this->destTilePositionY;
}

bool TileMovementComponent::_IsTileWalkable(const unsigned int x, const unsigned int y) const
{
	if (x >= this->tileMap->GetSizeX())
	{
		return false;
	}
	if (y >= this->tileMap->GetSizeY())
	{
		return false;
	}
	const Tile& tile = tileMap->GetTile(x, y);
	return tile.isWalkable;
}
