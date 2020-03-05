#ifndef TILEMAP_H
#define TILEMAP_H

enum TileType
{
	None,
	Dot,
	BigDot,
	Wall
};

struct Tile
{
	int x = 0;
	int y = 0;
	TileType type = TileType::None;
	bool isWalkable = false;
};

class TileMap
{
private:
	int rows = 0;
	int cols = 0;
	Tile* map;

public:
	TileMap(int sizex, int sizey);
	~TileMap();
	Tile GetTile(int x, int y) const;
	void SetTile(int x, int y, const Tile& tile);
	int GetSizeX() const;
	int GetSizeY() const;
};
#endif // TILEMAP_H
