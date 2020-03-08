#ifndef TILEMOVEMENTCOMPONENT_H
#define TILEMOVEMENTCOMPONENT_H

#include "../Component.h"

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
	int inputX = 0;
	int inputY = 0;
	int directionX = 0;
	int directionY = 0;
	float speed = 1.0f;

public:
	TileMovementComponent();
	~TileMovementComponent() override;
	void Start() override;
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void SetSpeed(const float& speed);	
	unsigned int GetCurrentTileX() const;
	unsigned int GetCurrentTileY() const;
	void SetCurrentTile(const unsigned int x, const unsigned int y);	
	unsigned int GetDestinationTileX() const;
	unsigned int GetDestinationTileY() const;
	bool SetDestination(const unsigned int x, const unsigned int y);	
	int GetMovementDirectionX() const;
	int GetMovementDirectionY() const;	
	bool IsAtDestination() const;

protected:
	void _Update(const float& deltaTime) override;

private:
	void _SetMovementDirection(const int x, const int y);
	bool _IsTileWalkable(const unsigned int x, const unsigned int y) const;
};
#endif // TILEMOVEMENTCOMPONENT_H