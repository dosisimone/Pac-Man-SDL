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

Tile* TileMap::GetTile(unsigned int x, unsigned int y) const
{
	if (!AreCoordsValid(x, y))
	{
		return nullptr;
	}
	return &map[x + cols * y];
}

void TileMap::SetTile(unsigned int x, unsigned int y, Tile& tile)
{
	if (!AreCoordsValid(x,y))
	{
		return;
	}
	tile.x = x;
	tile.y = y;
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

unsigned int TileMap::WorldPositionToTilePositionX(const float x)
{
	float tileMapSizeX = (float)GetSizeX() - 1;
	return (unsigned int)((x / distanceBtwTiles) + tileMapSizeX / 2.f);
}

unsigned int TileMap::WorldPositionToTilePositionY(const float y)
{
	float tileMapSizeY = (float)GetSizeY() - 1;
	return (unsigned int)((y / distanceBtwTiles) + tileMapSizeY / 2.f);
}

bool TileMap::AreCoordsValid(const unsigned int x, const unsigned int y) const
{
	return (x < cols && y < rows);
}
