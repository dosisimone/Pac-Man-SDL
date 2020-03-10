#include "TileMapPositionComponent.h"
#include "../../GameObject.h"
#include "../../GameController.h"
#include "../GameControllerComponent.h"
#include "../../TileMap.h"

TileMapPositionComponent::TileMapPositionComponent()
{
	this->tileMap = nullptr;
}

TileMapPositionComponent::~TileMapPositionComponent()
{
}

void TileMapPositionComponent::Awake()
{
	GameControllerComponent* gameControllerComponent = GameController::Instance->GetComponent<GameControllerComponent>();
	this->tileMap = gameControllerComponent->GetTileMap();
}

TileMap* TileMapPositionComponent::GetTileMap() const
{
	return this->tileMap;
}

void TileMapPositionComponent::SetTilePosition(const unsigned int x, const unsigned int y)
{
	GetOwner()->Position = tileMap->GetTileWorldPosition(x, y);
}

unsigned int TileMapPositionComponent::GetTilePositionX() const
{
	return tileMap->WorldPositionToTilePositionX(GetOwner()->Position.X);
}

unsigned int TileMapPositionComponent::GetTilePositionY() const
{
	return tileMap->WorldPositionToTilePositionY(GetOwner()->Position.Y);
}
