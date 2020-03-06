#include "TileMap.h"

TileMap::TileMap(unsigned int sizex, unsigned int sizey, float distanceBtwTiles)
{
	if (sizex < 1 || sizey < 1)
	{
		return;
	}
	this->rows = sizey;
	this->cols = sizex;	
	this->map = new Tile[rows * cols];
	this->distanceBtwTiles = distanceBtwTiles;
}

TileMap::~TileMap()
{
	delete[] map;
}

float TileMap::GetDistanceBtwTiles() const
{
	return this->distanceBtwTiles;
}

void TileMap::SetDistanceBtwTiles(const float distanceBtwTiles)
{
	if (distanceBtwTiles < 0.f) 
	{
		return;
	}
	this->distanceBtwTiles = distanceBtwTiles;
}

Tile TileMap::GetTile(unsigned int x, unsigned int y) const
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

void TileMap::SetTile(unsigned int x, unsigned int y, const Tile& tile)
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
	//map[x + cols * y].x = x;
	//map[x + cols * y].y = y;
}

unsigned int TileMap::GetSizeX() const
{
	return cols;
}

unsigned int TileMap::GetSizeY() const
{
	return rows;
}
