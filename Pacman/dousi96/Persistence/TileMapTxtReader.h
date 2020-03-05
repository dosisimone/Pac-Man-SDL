#ifndef TILEMAPTXTREADER_H
#define TILEMAPTXTREADER_H

class TileMap;

class TileMapTxtReader
{
public:
	TileMapTxtReader() = default;
	~TileMapTxtReader() = default;
	TileMap* Read(const char* path);
};
#endif // TILEMAPTXTREADER_H