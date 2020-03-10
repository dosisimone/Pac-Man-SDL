#include "GhostPathfinderComponent.h"
#include "TileMapPositionComponent.h"
#include "TileMovementComponent.h"
#include "../../TileMap.h"
#include "../../GameObject.h"

GhostPathfinderComponent::GhostPathfinderComponent()
{
	this->tileMapPositionComponent = nullptr;
	this->tileMapMovementComponent = nullptr;
	this->target = nullptr;
	this->movementDirectionX = 0;
	this->movementDirectionY = 0;
	this->strictObstacleAvoidance = false;
}

GhostPathfinderComponent::~GhostPathfinderComponent()
{
}

void GhostPathfinderComponent::Awake()
{
	this->tileMapPositionComponent = GetOwner()->GetComponent<TileMapPositionComponent>();
	this->tileMapMovementComponent = GetOwner()->GetComponent<TileMovementComponent>();
}

void GhostPathfinderComponent::SetTarget(const unsigned int x, const unsigned int y, const bool allowBackTurn)
{
	TileMap* tilemap = this->tileMapPositionComponent->GetTileMap();
	if (!tilemap->AreCoordsValid(x, y))
	{
		return;
	}

	this->target = tilemap->GetTile(x, y);

	if (allowBackTurn) 
	{
		this->movementDirectionX = 0;
		this->movementDirectionY = 0;
	}

	_CalcNextDestination();
}

bool GhostPathfinderComponent::IsAtFinalDestination() const
{
	return (this->tileMapMovementComponent->GetCurrentTileX() == this->target->x && this->tileMapMovementComponent->GetCurrentTileY() == this->target->y);
}

void GhostPathfinderComponent::SetStrictObstacleAvoidance(const bool strictObstacleAvoidance)
{
	this->strictObstacleAvoidance = strictObstacleAvoidance;
}

void GhostPathfinderComponent::_Update(const float& deltaTime)
{
	if (this->target == nullptr) 
	{
		return;
	}

	if (IsAtFinalDestination()) 
	{
		return;
	}

	if (this->tileMapMovementComponent->IsAtDestination())
	{
		_CalcNextDestination();
	}
}

void GhostPathfinderComponent::_CalcNextDestination()
{
	TileMap* tilemap = this->tileMapPositionComponent->GetTileMap();
	const int kSizeX = (int)tilemap->GetSizeX();
	const int kSizeY = (int)tilemap->GetSizeY();
	const int kCurrX = (int)this->tileMapMovementComponent->GetCurrentTileX();
	const int kCurrY = (int)this->tileMapMovementComponent->GetCurrentTileY();

	const int kOldMoveDirX = this->movementDirectionX;
	const int kOldMoveDirY = this->movementDirectionY;

	bool wayfound = false;
	int minSqrDistance = (kSizeX * kSizeX) + (kSizeY * kSizeY) + 1;
	// right
	{
		const int kRightCoordX = (kCurrX + 1) % kSizeX;
		Tile* right = tilemap->GetTile(kRightCoordX, kCurrY);
		if (_IsWalkable(right) && kOldMoveDirX != -1)
		{
			int sqrDistance = _GetSqrDistance(target, right);
			if (sqrDistance < minSqrDistance)
			{
				this->tileMapMovementComponent->SetDestination(right->x, right->y);
				this->movementDirectionX = 1;
				this->movementDirectionY = 0;
				minSqrDistance = sqrDistance;
				wayfound = true;
			}
		}
	}
	// up
	{
		const int kUpCoordY = (kCurrY + 1) % kSizeY;
		Tile* up = tilemap->GetTile(kCurrX, kUpCoordY);
		if (_IsWalkable(up) && kOldMoveDirY != -1)
		{
			int sqrDistance = _GetSqrDistance(target, up);
			if (sqrDistance < minSqrDistance)
			{
				this->tileMapMovementComponent->SetDestination(up->x, up->y);
				this->movementDirectionX = 0;
				this->movementDirectionY = 1;
				minSqrDistance = sqrDistance;
				wayfound = true;
			}
		}
	}
	// left
	{
		const int kLeftCoordX = (kCurrX + kSizeX - 1) % kSizeX;
		Tile* left = tilemap->GetTile(kLeftCoordX, kCurrY);
		if (_IsWalkable(left) && kOldMoveDirX != 1)
		{
			int sqrDistance = _GetSqrDistance(target, left);
			if (sqrDistance < minSqrDistance)
			{
				this->tileMapMovementComponent->SetDestination(left->x, left->y);
				this->movementDirectionX = -1;
				this->movementDirectionY = 0;
				minSqrDistance = sqrDistance;
				wayfound = true;
			}
		}
	}
	// down
	{
		const int kDownCoordY = (kCurrY + kSizeY - 1) % kSizeY;
		Tile* down = tilemap->GetTile(kCurrX, kDownCoordY);
		if (_IsWalkable(down) && kOldMoveDirY != 1)
		{
			int sqrDistance = _GetSqrDistance(target, down);
			if (sqrDistance < minSqrDistance)
			{
				this->tileMapMovementComponent->SetDestination(down->x, down->y);
				this->movementDirectionX = 0;
				this->movementDirectionY = -1;
				minSqrDistance = sqrDistance;
				wayfound = true;
			}
		}
	}

	if (!wayfound) 
	{
		this->target = tilemap->GetTile(kCurrX, kCurrY);
	}
}

bool GhostPathfinderComponent::_IsWalkable(Tile* tile) const
{
	return (this->strictObstacleAvoidance) ? tile->isEnemyWalkabe && tile->isPlayerWalkable : tile->isEnemyWalkabe;
}

int GhostPathfinderComponent::_GetSqrDistance(Tile* t1, Tile* t2) const
{
	const int t1x_minus_t2x = (int)t1->x - (int)t2->x;
	const int t1y_minus_t2y = (int)t1->y - (int)t2->y;
	return (t1x_minus_t2x * t1x_minus_t2x) + (t1y_minus_t2y * t1y_minus_t2y);
}
