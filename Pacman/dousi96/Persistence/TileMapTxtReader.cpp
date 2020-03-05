#include "TileMapTxtReader.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "../TileMap.h"

using namespace std;

TileMap* TileMapTxtReader::Read(const char* path)
{
	std:vector<std::string> lines;

	std::ifstream myfile(path);
	if (!myfile.is_open())
	{
		return nullptr;
	}

	int rows = 0;
	int cols = 0;
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

	for (int y = 0; y < lines.size(); ++y) 
	{
		int myY = lines.size() - 1 - y;
		for (int x = 0; x < lines[y].length(); x++)
		{
			Tile tile;
			switch (lines[y][x])
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
			default:
				tile.type = TileType::None;
				tile.isWalkable = true;
				break;
			}
			tileMap->SetTile(x, myY, tile);
		}
	}	

	return tileMap;
}
