#include <fstream>
#include <sstream>
#include "MapEditor.h"
#include "../GameMap.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Game.h"
#include "../../../Game/Scene/Scene.h"
#include "../../Actor/Tile/Tile.h"
#include "../../../Game/Input/KeyBoard.h"
#include "../../../Game/Input/Mouse.h"
#include "../../../Game/Graphics/Mesh/SpriteComponent.h"


MapEditor::MapEditor(const std::weak_ptr<class Scene>& scene)
	: mScene(scene)
	, mMapSelector({ nullptr, {10, 10} })
	, mBoardSelector({ nullptr, {-1, -1 } })
	, mTimeSelector({ nullptr, {0, 0} })
{
	loadData();
}

MapEditor::~MapEditor()
{
	mMapSelector.mSelector->setState(Actor::State::Dead);
	mBoardSelector.mSelector->setState(Actor::State::Dead);
}

void MapEditor::editInput()
{
	auto game = mScene.lock()->getGame().lock();

	if (game->getMouse()->getState(GLUT_RIGHT_BUTTON))
	{
		mClickPos = game->getMouse()->getPosition();
		checkTileIndex();
		checkBoard();
		checkTime();
	}
	if (game->getKeyBoard()->isKeyPressed('r') && game->getKeyBoard()->isKeyFirst('r'))
	{
		rotateTile();
	}
}

void MapEditor::loadData()
{
	auto game = mScene.lock()->getGame().lock();

	mMapSelector.mSelector = std::make_shared<Actor>(mScene);
	mMapSelector.mSelector->initailize();
	auto borderMap = std::make_shared<SpriteComponent>(mMapSelector.mSelector, game->getRenderer());
	borderMap->setTexture(game->getRenderer()->getTexture("Asset/Image/EditScene/select_border.png"));
	borderMap->initailize();

	mBoardSelector.mSelector = std::make_shared<Actor>(mScene);
	mBoardSelector.mSelector->setPosition(Vector3(-10000.0f, 0.0f, 0.0f));
	mBoardSelector.mSelector->setScale(2.5f);
	mBoardSelector.mSelector->initailize();
	auto borderBoard = std::make_shared<SpriteComponent>(mBoardSelector.mSelector, game->getRenderer(), 600);
	borderBoard->setTexture(game->getRenderer()->getTexture("Asset/Image/EditScene/select_border.png"));
	borderBoard->initailize();

	mTimeSelector.mSelector = std::make_shared<Actor>(mScene);
	mTimeSelector.mSelector->setPosition(Vector3(-10000.0f, 0.0f, 0.0f));
	mTimeSelector.mSelector->setScale(2.5f);
	mTimeSelector.mSelector->initailize();

	auto borderTime = std::make_shared<SpriteComponent>(mTimeSelector.mSelector, game->getRenderer(), 600);
	borderTime->setTexture(game->getRenderer()->getTexture("Asset/Image/EditScene/select_border.png"));
	borderTime->initailize();

}

void  MapEditor::setGameMap(const std::weak_ptr<class GameMap>& gameMap)
{
	mGameMap = gameMap;
}

void MapEditor::setBoard(const std::string& type, const Vector2& pos, const Vector2& size)
{
	if (type == "Left")
	{
		mLeftBoard.mPos = pos;
		mLeftBoard.mSize = size;
	}
	else if (type == "Right")
	{
		mRightBoard.mPos = pos;
		mRightBoard.mSize = size;
	}
	else
	{
		mTimeBoard.mPos = pos;
		mTimeBoard.mSize = size;
	}
}

void MapEditor::changeTile()
{
	auto index = mBoardSelector.mIndex.first * 10 + mBoardSelector.mIndex.second;
	auto type = "";
	switch (index)
	{
	case 0: type = "Road"; break;
	case 1: type = "Basic"; break;
	case 10: type = "Rock"; break;
	case 11: type = "Hill"; break;
	case 12: type = "Crystal"; break;
	case 20: type = "Tree"; break;
	case 21: type = "TreeDouble"; break;
	case 22: type = "TreeQuad"; break;
	case 30: type = "StartPoint"; changeStartTile(); break;
	case 31: type = "EndPoint"; changeEndTile(); break;
	case 32: type = "SnowBasic"; break;
	case 40: type = "SnowRock"; break;
	case 41: type = "SnowHill"; break;
	case 42: type = "SnowCrystal"; break;
	case 50: type = "SnowTree"; break;
	case 51: type = "SnowTreeDouble"; break;
	case 52: type = "SnowTreeQuad"; break;
	case 60: type = "TowerRoundA"; break;
	case 61: type = "TowerRoundC"; break;
	case 62: type = "TowerBlaster"; break;
	case 70: type = "TowerSquareA"; break;
	case 71: type = "TowerSquareB"; break;
	case 72: type = "TowerSquareC"; break;
	case 80: type = "TowerBallista"; break;
	case 81: type = "TowerCannon"; break;
	case 82: type = "TowerCatapult"; break;
	default: return;
	}

	mGameMap.lock()->removeTile(mMapSelector.mIndex.first, mMapSelector.mIndex.second);
	mGameMap.lock()->addTile(type, mMapSelector.mIndex.first, mMapSelector.mIndex.second, 0);
}

void MapEditor::rotateTile()
{
	mGameMap.lock()->rotTile(mMapSelector.mIndex.first, mMapSelector.mIndex.second);
}

void MapEditor::changeStartTile()
{
	auto index = mGameMap.lock()->getStartPosIndex();
	mGameMap.lock()->removeTile(index.first, index.second);
	mGameMap.lock()->addTile("Basic", index.first, index.second, 0);
}

void MapEditor::changeEndTile()
{
	auto index = mGameMap.lock()->getEndPosIndex();
	mGameMap.lock()->removeTile(index.first, index.second);
	mGameMap.lock()->addTile("Basic", index.first, index.second, 0);
}

void MapEditor::changeTime()
{
	auto index = mTimeSelector.mIndex.first * 10 + mTimeSelector.mIndex.second;
	auto type = "";
	switch (index)
	{
	case 0: type = "Sunny"; break;
	case 1: type = "Sunset"; break;
	case 2: type = "Moon"; break;
	default: break;
	}

	mGameMap.lock()->setTime(type);
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
		mMapSelector.mIndex =
		{	static_cast<int>((mapUpLeft.z - mClickPos.y) / tileSize), 
			static_cast<int>((mClickPos.x - mapUpLeft.x) / tileSize) };

		auto selectXPos = mapPos.x + mMapSelector.mIndex.second * tileSize;
		auto selectYPos = mapPos.z - mMapSelector.mIndex.first * tileSize;
		mMapSelector.mSelector->setPosition(Vector3(selectXPos, selectYPos, 0.0f));

		changeTile();
	}
}

void MapEditor::checkBoard()
{
	auto tileSize = 80.0f;

	if (mLeftBoard.mPos.x < mClickPos.x && mClickPos.x < mLeftBoard.mPos.x + mLeftBoard.mSize.x &&
		mLeftBoard.mPos.y > mClickPos.y && mClickPos.y > mLeftBoard.mPos.y - mLeftBoard.mSize.y)
	{		
		mBoardSelector.mIndex = 
		{ static_cast<int>((mLeftBoard.mPos.y - mClickPos.y) / 100.0f),
			static_cast<int>((mClickPos.x - mLeftBoard.mPos.x) / 100.0f) };

		auto selectXPos = mLeftBoard.mPos.x + 15 + mBoardSelector.mIndex.second * (15 + tileSize) + tileSize / 2;
		auto selectYPos = mLeftBoard.mPos.y - 20 - mBoardSelector.mIndex.first * (15 + tileSize) - tileSize / 2;
		mBoardSelector.mSelector->setPosition(Vector3(selectXPos, selectYPos, 0.0f));
	}
	else if (mRightBoard.mPos.x < mClickPos.x && mClickPos.x < mRightBoard.mPos.x + mRightBoard.mSize.x &&
		mRightBoard.mPos.y > mClickPos.y && mClickPos.y > mRightBoard.mPos.y - mRightBoard.mSize.y)
	{
		mBoardSelector.mIndex =
		{ static_cast<int>((mRightBoard.mPos.y - mClickPos.y) / 100.0f) + 6,
			static_cast<int>((mClickPos.x - mRightBoard.mPos.x) / 100.0f) };

		auto selectXPos = mRightBoard.mPos.x + 15 + mBoardSelector.mIndex.second * (15 + tileSize) + tileSize / 2;
		auto selectYPos = mRightBoard.mPos.y - 20 - (mBoardSelector.mIndex.first - 6) * (15 + tileSize) - tileSize / 2;
		mBoardSelector.mSelector->setPosition(Vector3(selectXPos, selectYPos, 0.0f));
	}
}

void MapEditor::checkTime()
{
	auto tileSize = 80.0f;
	
	if (mTimeBoard.mPos.x < mClickPos.x && mClickPos.x < mTimeBoard.mPos.x + mTimeBoard.mSize.x &&
		mTimeBoard.mPos.y > mClickPos.y && mClickPos.y > mTimeBoard.mPos.y - mTimeBoard.mSize.y)
	{
		mTimeSelector.mIndex = 
		{ static_cast<int>((mTimeBoard.mPos.y - mClickPos.y) / 100.0f),
			static_cast<int>((mClickPos.x - mTimeBoard.mPos.x) / 100.0f) };

		auto selectXPos = mTimeBoard.mPos.x + 15 + mTimeSelector.mIndex.second * (15 + tileSize) + tileSize / 2;
		auto selectYPos = mTimeBoard.mPos.y - 20 - mTimeSelector.mIndex.first * (15 + tileSize) - tileSize / 2;
		mTimeSelector.mSelector->setPosition(Vector3(selectXPos, selectYPos, 0.0f));

		changeTime();
	}
}