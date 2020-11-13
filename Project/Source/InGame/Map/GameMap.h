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
	GameMap(const std::weak_ptr<class Game>& game, const Vector2& size = Vector2(20, 20));
	~GameMap() noexcept;

	bool loadMap(const std::string& fileName);
	//bool saveMap();

	void addTile(const std::string& type, int y, int x);
	void addTile(const std::weak_ptr<class Tile>& tile, int y, int x);
	void removeTile(const std::weak_ptr<class Tile>& tile, int y, int x);

	const Vector2& getMapSize() const { return mMapSize; }
	const Vector3& getPosition() const { return mPosition; }
	float getTileSize() const { return mTileSize; }
	const std::vector<std::vector<std::weak_ptr<class Tile>>>& getTiles() { return mTiles; }

private:
	std::weak_ptr<class Game> mGame;
	Vector2 mMapSize;
	Vector3 mPosition;
	float mTileSize;
	std::vector<std::vector<std::weak_ptr<class Tile>>> mTiles;
};
