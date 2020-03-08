#ifndef TILEMAP_H
#define TILEMAP_H

class Vector2f;

enum class TileType : short
{
	None,
	Dot,
	BigDot,
	Wall,
	Teleport,
	GhostPen,
	GhostPenPortal
};

struct Tile
{
	TileType type = TileType::None;
	bool isWalkable = false;
};

class TileMap
{
private:
	unsigned int rows = 0;
	unsigned int cols = 0;
	float distanceBtwTiles = 1.f;
	Tile* map = nullptr;

public:
	TileMap(unsigned int sizex, unsigned int sizey, float distanceBtwTiles = 1.f);
	~TileMap();
	float GetDistanceBtwTiles() const;
	void SetDistanceBtwTiles(const float distanceBtwTiles);
	Tile GetTile(unsigned int x, unsigned int y) const;
	void SetTile(unsigned int x, unsigned int y, const Tile& tile);
	unsigned int GetSizeX() const;
	unsigned int GetSizeY() const;
	Vector2f GetTileWorldPosition(const unsigned int x, const unsigned int y) const;
};
#endif // TILEMAP_H
