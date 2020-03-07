#ifndef TILEMOVEMENTCOMPONENT_H
#define TILEMOVEMENTCOMPONENT_H

#include "Component.h"

class TileMap;
class TileMapPositionComponent;

class TileMovementComponent : public Component
{
private:
	TileMap* tileMap = nullptr;
	TileMapPositionComponent* tileMapPositionComponent = nullptr;
	unsigned int currTilePositionX = 0;
	unsigned int currTilePositionY = 0;
	unsigned int destTilePositionX = 0;
	unsigned int destTilePositionY = 0;	

public:
	TileMovementComponent();
	~TileMovementComponent() override;
	void Start() override;
	void Update(const float deltaTime) override {};
	bool IsAtDestination() const;
	
	void SetCurrentTile(const unsigned int x, const unsigned int y);
	unsigned int GetCurrentTileX() const;
	unsigned int GetCurrentTileY() const;
	bool SetDestination(const unsigned int x, const unsigned int y);
	unsigned int GetDestinationTileX() const;
	unsigned int GetDestinationTileY() const;

private:
	bool _IsTileWalkable(const unsigned int x, const unsigned int y) const;
};
#endif // TILEMOVEMENTCOMPONENT_H