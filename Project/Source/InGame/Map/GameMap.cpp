#include <fstream>
#include <sstream>
#include <cmath>
#include "GameMap.h"
#include "../../Game/Graphics/Renderer/Renderer.h"
#include "../../Game/Game.h"
#include "../../Game/Graphics/Light/Light.h"
#include "../Actor/Tile/Tile.h"
#include "../Actor/Tile/LightTile.h" 
#include "../Actor/Tile/EnemyTile.h"
#include "../Actor/Tile/EndPointTile.h"

GameMap::GameMap(const std::weak_ptr<class Scene>& scene, float tileSize, int mapSize)
	: mScene(scene)
	, mFileName("")
	, mTileSize(tileSize)
	, mMapSize(mapSize)
	, mPosition(Vector3(-mTileSize * mapSize / 2, 0.0f, mTileSize* mapSize / 2))
	, mStartPosition(Vector3::Zero)
	, mEndPosition(Vector3::Zero)
	, mTime("Sunny")
	, mMinionCount(0)
{
	mTiles.resize(mapSize, std::vector<std::weak_ptr<class Tile>>(mapSize));
}

GameMap::~GameMap()
{
	for (auto& y : mTiles)
	{
		for (auto& x : y)
		{
			if (!x.expired())
			{
				x.lock()->setState(Actor::State::Dead);
			}
		}
	}
}

bool GameMap::loadMap(const std::string& fileName, const std::string time)
{
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
		else if (prefix == "Time")
		{
			if (time == "None")
			{
				ss >> mTime;
			}
			else
			{
				mTime = time;
			}
			addDirectionalLight();
		}
		else if (prefix == "Minion")
		{
			ss >> mMinionCount;
		}
	}

	std::cerr << fileName << " load complete\n";
	mFileName = fileName;
	return true;
}

void GameMap::addTile(const std::string& type, int y, int x, float rot)
{
	Vector3 position(mPosition.x + x * mTileSize, mPosition.y, mPosition.z - y * mTileSize);
	std::shared_ptr<Tile> tile = nullptr;
	switch (HashCode(type.c_str()))
	{
	case HashCode("Basic"): tile = std::make_shared<Tile>(mScene); break;
	case HashCode("Road"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Road); break;
	case HashCode("Light"): tile = std::make_shared<LightTile>(mScene, mScene.lock()->getGame().lock()->getRenderer()->getLight(), mTime); break;
	case HashCode("Rock"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Rock); break;
	case HashCode("Hill"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Hill); break;
	case HashCode("Crystal"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Crystal); break;
	case HashCode("Tree"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Tree); break;
	case HashCode("TreeDouble"): tile = std::make_shared<Tile>(mScene, Tile::TileType::TreeDouble); break;
	case HashCode("TreeQuad"): tile = std::make_shared<Tile>(mScene, Tile::TileType::TreeQuad); break;
	case HashCode("StartPoint"): tile = std::make_shared<Tile>(mScene, Tile::TileType::StartPoint); setStartPosition(position); break;
	case HashCode("EndPoint"): tile = std::make_shared<EndPointTile>(mScene); setEndPosition(position); break;
	case HashCode("SnowBasic"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Snow_Basic); break;
	case HashCode("SnowRock"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Snow_Rock); break;
	case HashCode("SnowHill"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Snow_Hill); break;
	case HashCode("SnowCrystal"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Snow_Crystal); break;
	case HashCode("SnowTree"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Snow_Tree); break;
	case HashCode("SnowTreeDouble"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Snow_TreeDouble); break;
	case HashCode("SnowTreeQuad"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Snow_TreeQuad); break;
	case HashCode("TowerRoundA"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Tower_RoundA); break;
	case HashCode("TowerRoundC"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Tower_RoundC); break;
	case HashCode("TowerBlaster"): tile = std::make_shared<EnemyTile>(mScene, Tile::TileType::Tower_Blaster); break;
	case HashCode("TowerSquareA"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Tower_SquareA); break;
	case HashCode("TowerSquareB"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Tower_SquareB); break;
	case HashCode("TowerSquareC"): tile = std::make_shared<Tile>(mScene, Tile::TileType::Tower_SquareC); break;
	case HashCode("TowerBallista"): tile = std::make_shared<EnemyTile>(mScene, Tile::TileType::Tower_Ballista); break;
	case HashCode("TowerCannon"): tile = std::make_shared<EnemyTile>(mScene, Tile::TileType::Tower_Cannon); break;
	case HashCode("TowerCatapult"): tile = std::make_shared<EnemyTile>(mScene, Tile::TileType::Tower_Catapult); break;
	default: break;
	}
	tile->setScale(mTileSize);
	tile->setRotation(Quaternion(Vector3::UnitY, Math::ToRadians(rot)));
	tile->setPosition(position);
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

void GameMap::addDirectionalLight()
{
	const auto& light = mScene.lock()->getGame().lock()->getRenderer()->getLight();

	light->resetAllLight();
	
	DirectionalLight dirLight;
	
	if (mTime == "Sunny")
	{
		light->setAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
		dirLight.direction = Vector3(0.0f, -1.0f, 0.0f);
		dirLight.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
		dirLight.specularColor = Vector3(0.8f, 0.8f, 0.8f);
		dirLight.intensity = 1.0f;
	}
	else if (mTime == "Sunset")
	{
		light->setAmbientLight(Vector3(0.25f, 0.25f, 0.25f));
		dirLight.direction = Vector3(-1.0f, 0.2f, 0.0f);
		dirLight.diffuseColor = Vector3::Rgb(255.0f, 100.0f, 100.0f);
		dirLight.specularColor = Vector3(0.9f, 0.9f, 0.9f);
		dirLight.intensity = 1.0f;
	}
	else
	{
		light->setAmbientLight(Vector3(0.1f, 0.1f, 0.1f));
		dirLight.direction = Vector3(0.0f, -1.0f, 0.0f);
		dirLight.diffuseColor = Vector3(0.7f, 0.7f, 0.7f);
		dirLight.specularColor = Vector3(0.3f, 0.3f, 0.3f);
		dirLight.intensity = 0.1f;
	}

	light->addDirectionalLight(std::make_shared<DirectionalLight>(dirLight));
}

bool GameMap::checkTileRange(int y, int x)
{
	if (y < 0 || x < 0 || y >= mMapSize || x >= mMapSize)
		return false;
	return true;
}

const std::vector<std::weak_ptr<class Tile>> GameMap::getCollideTiles(const Vector3& pos)
{
	std::vector<std::weak_ptr<class Tile>> cTile;

	int x = static_cast<int>(pos.x - mPosition.x) / mTileSize;
	int y = static_cast<int>(pos.z - mPosition.z) / -mTileSize;

	cTile.push_back(mTiles[y][x]);
	for (auto i = 0; i < 8; i++)
	{
		if (checkTileRange(y + TILEROUND[i][0], x + TILEROUND[i][1]))
		{
			cTile.push_back(mTiles[y + TILEROUND[i][0]][x + TILEROUND[i][1]]);
		}
	}

	return cTile;
}