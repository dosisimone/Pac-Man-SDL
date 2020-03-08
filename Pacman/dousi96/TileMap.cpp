#include "TileMap.h"
#include "../Vector2f.h"

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
}

unsigned int TileMap::GetSizeX() const
{
	return cols;
}

unsigned int TileMap::GetSizeY() const
{
	return rows;
}

Vector2f TileMap::GetTileWorldPosition(const unsigned int x, const unsigned int y) const
{
	float tileMapSizeX = (float)GetSizeX() - 1;
	float tileMapSizeY = (float)GetSizeY() - 1;
	float Xf = (float)x;
	float Yf = (float)y;
	Vector2f position;
	position.X = (Xf - tileMapSizeX / 2.f) * distanceBtwTiles;
	position.Y = (Yf - tileMapSizeY / 2.f) * distanceBtwTiles;
	return position;
}
