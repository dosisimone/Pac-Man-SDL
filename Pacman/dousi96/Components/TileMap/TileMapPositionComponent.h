#ifndef TILEPOSITIONCOMPONENT_H
#define TILEPOSITIONCOMPONENT_H

#include "../Component.h"

class TileMap;

class TileMapPositionComponent : public Component
{
private:
	TileMap* tileMap = nullptr;

public:
	TileMapPositionComponent();
	~TileMapPositionComponent() override;
	void Awake() override;
	TileMap* GetTileMap() const;
	void SetTilePosition(const unsigned int x, const unsigned int y);
	unsigned int GetTilePositionX() const;
	unsigned int GetTilePositionY() const;	
};
#endif // TILEPOSITIONCOMPONENT_H