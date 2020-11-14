#include <fstream>
#include <sstream>
#include "MapEditor.h"
#include "../GameMap.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Game.h"
#include "../../Actor/Tile/Tile.h"
#include "../../../Game/Input/KeyBoard.h"
#include "../../../Game/Input/Mouse.h"


MapEditor::MapEditor(const std::weak_ptr<class Game>& game, const std::weak_ptr<class GameMap>& gameMap)
	: mGame(game)
	, mGameMap(gameMap)
	, mSelectTileIndex({ -1,-1 })
	, mIsSelectTile(false)
{
	loadData();
}

MapEditor::~MapEditor()
{

}

void MapEditor::editInput()
{
	auto game = mGame.lock();

	if (game->getMouse()->getState(GLUT_LEFT_BUTTON))
	{
		mClickPos = game->getMouse()->getPosition();
		mClickPos.y *= -1;
		checkTileIndex();
	}

	if (game->getKeyBoard()->isKeyPressed('1'))
	{
		auto mapSize = mGameMap.lock()->getMapSize();
		if (mSelectTileIndex.first >= 0 && mSelectTileIndex.first < mapSize &&
			mSelectTileIndex.second >= 0 && mSelectTileIndex.second < mapSize)
		{
			mGameMap.lock()->removeTile(mSelectTileIndex.first, mSelectTileIndex.second);
			mGameMap.lock()->addTile("Basic", mSelectTileIndex.first, mSelectTileIndex.second, 0);
		}
	}
	if (game->getKeyBoard()->isKeyPressed('2'))
	{
		auto mapSize = mGameMap.lock()->getMapSize();
		if (mSelectTileIndex.first >= 0 && mSelectTileIndex.first < mapSize &&
			mSelectTileIndex.second >= 0 && mSelectTileIndex.second < mapSize)
		{
			mGameMap.lock()->removeTile(mSelectTileIndex.first, mSelectTileIndex.second);
			mGameMap.lock()->addTile("Road", mSelectTileIndex.first, mSelectTileIndex.second, 0);
		}
	}

	if (game->getKeyBoard()->isSpecialKeyPressed(GLUT_KEY_END))
	{
		exit(0);
	}
}

void MapEditor::loadData()
{

}

void MapEditor::checkTileIndex()
{
	auto mapPos = mGameMap.lock()->getPosition();
	auto tileSize = mGameMap.lock()->getTileSize();
	auto mapSize = mGameMap.lock()->getMapSize();
	const auto& mapUpLeft = Vector3(mapPos.x - tileSize / 2, mapPos.y, mapPos.z + tileSize / 2);
	const auto& mapDownRight = Vector3(mapUpLeft.x + tileSize * mapSize, mapUpLeft.y, mapUpLeft.z - tileSize * mapSize);

	if (mapUpLeft.x < mClickPos.x && mClickPos.x < mapDownRight.x &&
		mapUpLeft.z > mClickPos.y && mClickPos.y > mapDownRight.z)
	{		
		mIsSelectTile = true;
		mSelectTileIndex = { 
			static_cast<int>((mapUpLeft.z - mClickPos.y) / tileSize), 
			static_cast<int>((mClickPos.x - mapUpLeft.x) / tileSize) };
	}
	else
	{
		mIsSelectTile = false;
		mSelectTileIndex = { -1, -1 };
	}
}
