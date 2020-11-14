#include <fstream>
#include <sstream>
#include "MapEditor.h"
#include "../GameMap.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Game.h"
#include "../../Actor/Tile/Tile.h"
#include "../../../Game/Input/KeyBoard.h"
#include "../../../Game/Input/Mouse.h"
#include "../../../Game/Graphics/Mesh/SpriteComponent.h"


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
		mGameMap.lock()->saveMap();
	}
}

void MapEditor::loadData()
{
	mSelecter = std::make_shared<Actor>(mGame);
	mSelecter->initailize();
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

		auto selectXPos = mapPos.x + mSelectTileIndex.second * tileSize;
		auto selectYPos = mapPos.z - mSelectTileIndex.first * tileSize;
		mSelecter->setPosition(Vector3(selectXPos, selectYPos, 0.0f));
		mSelectBorder = std::make_shared<SpriteComponent>(mSelecter, mGame.lock()->getRenderer());
		mSelectBorder->setTexture(mGame.lock()->getRenderer()->getTexture("Asset/Image/EditScene/select_border.png"));
		mSelectBorder->initailize();
	}
	else
	{
		mIsSelectTile = false;
		mSelectTileIndex = { -1, -1 };
		mSelectBorder.reset();
	}
}
