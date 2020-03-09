#ifndef GHOSTPATHFINDERCOMPONENT_H
#define GHOSTPATHFINDERCOMPONENT_H

#include "../Component.h"

class TileMapPositionComponent;
class TileMovementComponent;
struct Tile;

class GhostPathfinderComponent : public Component
{
private:
	TileMapPositionComponent* tileMapPositionComponent = nullptr;
	TileMovementComponent* tileMapMovementComponent = nullptr;
	Tile* target = nullptr;
	int movementDirectionX = 0;
	int movementDirectionY = 0;
	bool strictObstacleAvoidance = false;

public:
	GhostPathfinderComponent();
	~GhostPathfinderComponent() override;
	void Awake() override;
	void SetTarget(const unsigned int x, const unsigned int y);	
	bool IsAtFinalDestination() const;
	void SetStrictObstacleAvoidance(const bool strictObstacleAvoidance);

protected:
	void _Update(const float& deltaTime) override;	
	void _CalcNextDestination();	
	bool _IsWalkable(Tile* tile) const;
	int _GetSqrDistance(Tile* t1, Tile* t2) const;
};
#endif // GHOSTPATHFINDERCOMPONENT_H