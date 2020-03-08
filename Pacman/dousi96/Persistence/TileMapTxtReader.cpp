#include "TileMapTxtReader.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "../TileMap.h"

TileMap* TileMapTxtReader::Read(const char* path)
{
	std::vector<std::string> lines;

	std::ifstream myfile(path);
	if (!myfile.is_open())
	{
		return nullptr;
	}

	unsigned int rows = 0;
	unsigned int cols = 0;
	std::string line;	
	while (!myfile.eof())
	{
		std::getline(myfile, line);		
		lines.push_back(line);
		cols = (line.length() > cols) ? line.length() : cols;
		++rows;
	}
	myfile.close();

	TileMap* tileMap = new TileMap(cols, rows);

	for (unsigned int col = 0; col < lines.size(); ++col) 
	{
		unsigned int y = lines.size() - 1 - col;
		for (unsigned int x = 0; x < lines[col].length(); x++)
		{
			Tile tile;
			switch (lines[col][x])
			{
			case 'x':
				tile.type = TileType::Wall;
				tile.isWalkable = false;
				break;
			case '.':
				tile.type = TileType::Dot;
				tile.isWalkable = true;
				break;
			case 'o':
				tile.type = TileType::BigDot;
				tile.isWalkable = true;
				break;
			case 'T':
				tile.type = TileType::Teleport;
				tile.isWalkable = true;
				break;
			case 'G':
				tile.type = TileType::GhostPen;
				tile.isWalkable = false;
				break;
			case 'P':
				tile.type = TileType::GhostPenPortal;
				tile.isWalkable = true;
				break;
			default:
				tile.type = TileType::None;
				tile.isWalkable = true;
				break;
			}
			tileMap->SetTile(x, y, tile);
		}
	}	

	return tileMap;
}
