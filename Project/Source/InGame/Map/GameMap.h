#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "../../Game/Math/Math.h"


constexpr unsigned int HashCode(const char* str)
{
    return str[0] ? static_cast<unsigned int>(str[0]) + 0xEDB8832Full * HashCode(str + 1) : 8603;
}

class GameMap : public std::enable_shared_from_this<GameMap>
{
public:
	GameMap(const std::weak_ptr<class Game>& game, float tileSize = 200.0f, int mapSize = 20);
	~GameMap() noexcept;

	bool loadMap(const std::string& fileName);
	bool saveMap();

	void addTile(const std::string& type, int y, int x, float rot);
	void removeTile(int y, int x);

	float getTileSize() const { return mTileSize; }
	int getMapSize() const { return mMapSize; }
	const Vector3& getPosition() const { return mPosition; }
	const std::vector<std::vector<std::weak_ptr<class Tile>>>& getTiles() { return mTiles; }

private:
	std::weak_ptr<class Game> mGame;
	float mTileSize;
	int mMapSize;
	Vector3 mPosition;
	std::vector<std::vector<std::weak_ptr<class Tile>>> mTiles;
};
