#include "TileMap.h"

TileMap::TileMap(int sizex, int sizey)
{
	if (sizex < 1 || sizey < 1)
	{
		return;
	}

	rows = sizey;
	cols = sizex;

	map = new Tile[rows * cols];	
}

TileMap::~TileMap()
{
	delete[] map;
}

Tile TileMap::GetTile(int x, int y) const
{
	if (x < 0 || x >= cols)
	{
		return Tile();
	}
	if (y < 0 || y >= rows)
	{
		return Tile();
	}
	return map[x + cols * y];
}

void TileMap::SetTile(int x, int y, const Tile& tile)
{
	if (x < 0 || x >= cols)
	{
		return;
	}
	if (y < 0 || y >= rows)
	{
		return;
	}
	map[x + cols * y] = tile;
	map[x + cols * y].x = x;
	map[x + cols * y].y = y;
}

int TileMap::GetSizeX() const
{
	return cols;
}

int TileMap::GetSizeY() const
{
	return rows;
}
