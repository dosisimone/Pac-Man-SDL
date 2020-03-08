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

TileMap* TileMapPositionComponent::GetTileMap() const
{
	return this->tileMap;
}

void TileMapPositionComponent::SetTileMap(TileMap* tileMap)
{
	if (tileMap == nullptr) 
	{
		return;
	}
	this->tileMap = tileMap;
}

void TileMapPositionComponent::SetTilePosition(const unsigned int x, const unsigned int y)
{
	GetOwner()->Position = tileMap->GetTileWorldPosition(x, y);
}

unsigned int TileMapPositionComponent::GetTilePositionX() const
{
	float distanceBtwTiles = tileMap->GetDistanceBtwTiles();
	float tileMapSizeX = (float)tileMap->GetSizeX() - 1;
	unsigned int x = (unsigned int)(GetOwner()->Position.X / distanceBtwTiles + tileMapSizeX / 2.f);
	return x;
}

unsigned int TileMapPositionComponent::GetTilePositionY() const
{
	float distanceBtwTiles = tileMap->GetDistanceBtwTiles();
	float tileMapSizeY = (float)tileMap->GetSizeY() - 1;
	unsigned int y = (unsigned int)(GetOwner()->Position.Y / distanceBtwTiles + tileMapSizeY / 2.f);
	return y;
}
