#include <fstream>
#include <sstream>
#include "GameMap.h"
#include ".././../Game/Game.h"
#include "../Actor/Tile/Tile.h"

GameMap::GameMap(const std::weak_ptr<class Game>& game, const Vector2& size)
	: mGame(game)
	, mMapSize(size)
	, mPosition(Vector3(-500.0f, 0.0f, 500.0f))
	, mTileSize(200.0f)
{
	mTiles.resize(size.y, std::vector<std::weak_ptr<class Tile>>(size.x));
}

GameMap::~GameMap()
{

}

bool GameMap::loadMap(const std::string& fileName)
{
	//Open Obj file
	std::ifstream mapFile(fileName);

	if (!mapFile.is_open())
	{
		std::cerr << "file not found : " << fileName << '\n';
		return false;
	}

	std::stringstream ss;
	std::string line = "";
	std::string prefix = "";
	std::string tileName;
	unsigned int y = 0;
	unsigned int xSize = 0;

	while (std::getline(mapFile, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "Line")
		{
			ss >> y >> xSize;
		}
		else if (prefix == "Type")
		{
			for (auto x = 0; x < xSize; x++)
			{
				ss >> tileName;
				addTile(tileName, y - 1, x);
			}
		}
	}

	std::cerr << fileName << " load complete\n";

	return true;
}

void GameMap::addTile(const std::string& type, int y, int x)
{
	std::shared_ptr<Tile> tile = nullptr;
	switch (HashCode(type.c_str()))
	{
	case HashCode("Basic"):
		tile = std::make_shared<Tile>(mGame);
		break;
	default:
		break;
	}
	tile->setScale(mTileSize);
	tile->setPosition(Vector3(mPosition.x + x * mTileSize, mPosition.y, mPosition.z + y * mTileSize));
	tile->initailize();
	addTile(tile, y, x);
}

void GameMap::addTile(const std::weak_ptr<class Tile>& tile, int y, int x)
{
	mTiles[y][x] = tile;
}

void GameMap::removeTile(const std::weak_ptr<class Tile>& tile, int y, int x)
{
	
}