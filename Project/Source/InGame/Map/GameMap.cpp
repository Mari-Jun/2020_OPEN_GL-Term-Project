#include <fstream>
#include <sstream>
#include "GameMap.h"
#include "../../Game/Game.h"
#include "../Actor/Tile/Tile.h"

GameMap::GameMap(const std::weak_ptr<class Game>& game, float tileSize, int mapSize)
	: mGame(game)
	, mTileSize(tileSize)
	, mMapSize(mapSize)
	, mPosition(Vector3(-mTileSize * mapSize / 2, 0.0f, mTileSize * mapSize / 2))
{
	mTiles.resize(mapSize, std::vector<std::weak_ptr<class Tile>>(mapSize));
}

GameMap::~GameMap()
{
	for (auto& y : mTiles)
	{
		for (auto& x : y)
		{
			x.lock()->setState(Actor::State::Dead);
		}
	}
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
	float rot = 0.0f;

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
				ss >> tileName >> rot;
				addTile(tileName, y - 1, x, rot);
			}
		}
	}

	std::cerr << fileName << " load complete\n";

	return true;
}

void GameMap::addTile(const std::string& type, int y, int x, float rot)
{
	std::shared_ptr<Tile> tile = nullptr;
	switch (HashCode(type.c_str()))
	{
	case HashCode("Basic"):
		tile = std::make_shared<Tile>(mGame);
		break;
	case HashCode("Road"):
		tile = std::make_shared<Tile>(mGame, Tile::Type::Road);
		break;
	case HashCode("Straight"):
		tile = std::make_shared<Tile>(mGame, Tile::Type::Straight);
		break;
	default:
		break;
	}
	tile->setScale(mTileSize);
	tile->setRotation(Quaternion(Vector3::UnitY, Math::ToRadians(rot)));
	tile->setPosition(Vector3(mPosition.x + x * mTileSize, mPosition.y, mPosition.z - y * mTileSize));
	tile->initailize();
	mTiles[y][x] = tile;
}

void GameMap::removeTile(int y, int x)
{
	if (!mTiles[y][x].expired())
	{
		mTiles[y][x].lock()->setState(Actor::State::Dead);
	}
}