#include "TileMapPositionComponent.h"
#include "../GameController.h"

TileMapPositionComponent::TileMapPositionComponent()
{
	this->tileMap = nullptr;
}

TileMapPositionComponent::~TileMapPositionComponent()
{
}

void TileMapPositionComponent::Start()
{
	this->tileMap = GameController::Instance->GetTileMap();
}

Vector2f TileMapPositionComponent::GetTileWorldPosition(const unsigned int x, const unsigned int y) const
{
	float distanceBtwTiles = tileMap->GetDistanceBtwTiles();
	float tileMapSizeX = (float)tileMap->GetSizeX() - 1;
	float tileMapSizeY = (float)tileMap->GetSizeY() - 1;

	float Xf = (float)x;
	float Yf = (float)y;

	Vector2f position;
	position.X = (Xf - tileMapSizeX / 2.f) * distanceBtwTiles;
	position.Y = (Yf - tileMapSizeY / 2.f) * distanceBtwTiles;
	return position;
}

void TileMapPositionComponent::SetTilePosition(const unsigned int x, const unsigned int y)
{
	Owner->Position = GetTileWorldPosition(x, y);
}

unsigned int TileMapPositionComponent::GetTilePositionX() const
{
	float distanceBtwTiles = tileMap->GetDistanceBtwTiles();
	float tileMapSizeX = (float)tileMap->GetSizeX() - 1;
	unsigned int x = (unsigned int)(Owner->Position.X / distanceBtwTiles + tileMapSizeX / 2.f);
	return x;
}

unsigned int TileMapPositionComponent::GetTilePositionY() const
{
	float distanceBtwTiles = tileMap->GetDistanceBtwTiles();
	float tileMapSizeY = (float)tileMap->GetSizeY() - 1;
	unsigned int y = (unsigned int)(Owner->Position.Y / distanceBtwTiles + tileMapSizeY / 2.f);
	return y;
}
