#ifndef TILEMOVEMENTCOMPONENT_H
#define TILEMOVEMENTCOMPONENT_H

#include "../Component.h"

class TileMapPositionComponent;

class TileMovementComponent : public Component
{
private:
	TileMapPositionComponent* tileMapPositionComponent = nullptr;
	unsigned int currTilePositionX = 0;
	unsigned int currTilePositionY = 0;
	unsigned int destTilePositionX = 0;
	unsigned int destTilePositionY = 0;	
	float speed = 1.0f;

public:
	TileMovementComponent();
	~TileMovementComponent() override;
	void Awake() override;
	void Start() override;
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
};
#endif // TILEMOVEMENTCOMPONENT_H