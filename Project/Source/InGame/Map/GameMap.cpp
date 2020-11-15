#include <fstream>
#include <sstream>
#include "GameMap.h"
#include "../../Game/Game.h"
#include "../Actor/Tile/Tile.h"

GameMap::GameMap(const std::weak_ptr<class Game>& game, float tileSize, int mapSize)
	: mGame(game)
	, mFileName("")
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
	mFileName = fileName;

	return true;
}

bool GameMap::saveMap()
{
	if (mFileName.size() != 0)
	{
		//Open Obj file
		std::ofstream mapFile(mFileName);

		if (!mapFile.is_open())
		{
			std::cerr << "file not found : " << mFileName << '\n';
			return false;
		}

		std::stringstream ss;
		std::string line = "";
		std::string prefix = "";
		std::string tileName;
		unsigned int y = 0;
		unsigned int xSize = 0;
		float rot = 0.0f;

		for (auto y = 0; y < mTiles.size(); y++)
		{
			mapFile << "Line " << y + 1 << " " << mTiles.size() << '\n';
			mapFile << "Type ";
			for (const auto& x : mTiles[y])
			{
				auto rot = Math::ToDegrees(Math::Acos(Quaternion::Dot(Quaternion(Vector3::UnitY, 0), x.lock()->getRotation())));
				mapFile << x.lock()->getTypeToString() << ' ' << rot * 2 << ' ';
			}
			mapFile << '\n';
		}

		std::cerr << mFileName << " Save complete\n";

		return true;
	}
	return false;
}

void GameMap::addTile(const std::string& type, int y, int x, float rot)
{
	std::shared_ptr<Tile> tile = nullptr;
	switch (HashCode(type.c_str()))
	{
	case HashCode("Basic"): tile = std::make_shared<Tile>(mGame); break;
	case HashCode("Road"): tile = std::make_shared<Tile>(mGame, Tile::Type::Road); break;
	case HashCode("Rock"): tile = std::make_shared<Tile>(mGame, Tile::Type::Rock); break;
	case HashCode("Hill"): tile = std::make_shared<Tile>(mGame, Tile::Type::Hill); break;
	case HashCode("Crystal"): tile = std::make_shared<Tile>(mGame, Tile::Type::Crystal); break;
	case HashCode("Tree"): tile = std::make_shared<Tile>(mGame, Tile::Type::Tree); break;
	case HashCode("TreeDouble"): tile = std::make_shared<Tile>(mGame, Tile::Type::TreeDouble); break;
	case HashCode("TreeQuad"): tile = std::make_shared<Tile>(mGame, Tile::Type::TreeQuad); break;
	case HashCode("StartPoint"): tile = std::make_shared<Tile>(mGame, Tile::Type::StartPoint); break;
	case HashCode("EndPoint"): tile = std::make_shared<Tile>(mGame, Tile::Type::EndPoint); break;
	case HashCode("SnowBasic"): tile = std::make_shared<Tile>(mGame, Tile::Type::Snow_Basic); break;
	case HashCode("SnowRock"): tile = std::make_shared<Tile>(mGame, Tile::Type::Snow_Rock); break;
	case HashCode("SnowHill"): tile = std::make_shared<Tile>(mGame, Tile::Type::Snow_Hill); break;
	case HashCode("SnowCrystal"): tile = std::make_shared<Tile>(mGame, Tile::Type::Snow_Crystal); break;
	case HashCode("SnowTree"): tile = std::make_shared<Tile>(mGame, Tile::Type::Snow_Tree); break;
	case HashCode("SnowTreeDouble"): tile = std::make_shared<Tile>(mGame, Tile::Type::Snow_TreeDouble); break;
	case HashCode("SnowTreeQuad"): tile = std::make_shared<Tile>(mGame, Tile::Type::Snow_TreeQuad); break;
	default: break;
	}
	tile->setScale(mTileSize);
	tile->setRotation(Quaternion(Vector3::UnitY, Math::ToRadians(rot)));
	tile->setPosition(Vector3(mPosition.x + x * mTileSize, mPosition.y, mPosition.z - y * mTileSize));
	tile->initailize();
	mTiles[y][x] = tile;
}

void GameMap::removeTile(int y, int x)
{
	mTiles[y][x].lock()->setState(Actor::State::Dead);
}

void GameMap::rotTile(int y, int x)
{
	auto tile = mTiles[y][x].lock();
	tile->setRotation(Quaternion::Concatenate(tile->getRotation(), Quaternion(Vector3::UnitY, Math::ToRadians(90.0f))));
}