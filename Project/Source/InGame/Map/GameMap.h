#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "../../Game/Math/Math.h"

const int TILEROUND[8][2] = { {0,-1},{-1, -1}, {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1} };

constexpr unsigned int HashCode(const char* str)
{
    return str[0] ? static_cast<unsigned int>(str[0]) + 0xEDB8832Full * HashCode(str + 1) : 8603;
}

class GameMap : public std::enable_shared_from_this<GameMap>
{
public:
	GameMap(const std::weak_ptr<class Scene>& scene, float tileSize = 200.0f, int mapSize = 20);
	~GameMap() noexcept;

	bool loadMap(const std::string& fileName, const std::string time = "None");

	void addTile(const std::string& type, int y, int x, float rot);
	void removeTile(int y, int x);
	void rotTile(int y, int x);

private:
	std::weak_ptr<class Scene> mScene;
	std::string mFileName;
	float mTileSize;
	int mMapSize;
	Vector3 mPosition;
	std::vector<std::vector<std::weak_ptr<class Tile>>> mTiles;
	Vector3 mStartPosition;
	Vector3 mEndPosition;
	std::string mTime;
	int mMinionCount;

private:
	void addDirectionalLight();
	bool checkTileRange(int y, int x);

public:
	const std::string& getFileName() const { return mFileName; }
	float getTileSize() const { return mTileSize; }
	int getMapSize() const { return mMapSize; }
	const Vector3& getPosition() const { return mPosition; }
	const std::vector<std::vector<std::weak_ptr<class Tile>>>& getTiles() { return mTiles; }
	const std::vector<std::weak_ptr<class Tile>> getCollideTiles(const Vector3& pos);
	const Vector3& getStartPosition() const { return mStartPosition; }
	std::pair<int, int> getStartPosIndex() const { return {static_cast<int>((mStartPosition.z - mPosition.z) / -mTileSize) , static_cast<int>((mStartPosition.x - mPosition.x) / mTileSize) }; }
	const Vector3& getEndPosition() const { return mEndPosition; }
	std::pair<int, int> getEndPosIndex() const { return { static_cast<int>((mEndPosition.z - mPosition.z) / -mTileSize), static_cast<int>((mEndPosition.x - mPosition.x) / mTileSize) }; }
	const std::string& getTime() const { return mTime; }
	int getMinionCount() const { return mMinionCount; }
	void setStartPosition(const Vector3& pos) { mStartPosition = pos; }
	void setEndPosition(const Vector3& pos) { mEndPosition = pos; }
	void setTime(const std::string& time) { mTime = time; }
	void setMinionCount(int count) { mMinionCount = count; }
};
