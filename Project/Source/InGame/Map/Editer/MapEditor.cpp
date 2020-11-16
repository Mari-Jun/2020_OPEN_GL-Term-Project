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


MapEditor::MapEditor(const std::weak_ptr<class Scene>& scene, const std::weak_ptr<class GameMap>& gameMap)
	: mScene(scene)
	, mGameMap(gameMap)
	, mSelectMapIndex({ 10,10 })
	, mSelectBoardIndex({ -1,-1 })
	, mLeftBoardPos(Vector2::Zero)
{
	loadData();
}

MapEditor::~MapEditor()
{
	mSelectorMap->setState(Actor::State::Dead);
	mSelectorBoard->setState(Actor::State::Dead);
}

void MapEditor::editInput()
{
	auto game = mScene.lock()->getGame().lock();

	if (game->getMouse()->getState(GLUT_LEFT_BUTTON))
	{
		mClickPos = game->getMouse()->getPosition();
		checkTileIndex();
		checkLeftBoard();
		checkRightBoard();
	}
	if (game->getKeyBoard()->isKeyPressed('r') && game->getKeyBoard()->isKeyFirst('r'))
	{
		rotateTile();
	}
}

void MapEditor::loadData()
{
	auto game = mScene.lock()->getGame().lock();

	mSelectorMap = std::make_shared<Actor>(mScene);
	mSelectorMap->initailize();
	auto borderMap = std::make_shared<SpriteComponent>(mSelectorMap, game->getRenderer());
	borderMap->setTexture(game->getRenderer()->getTexture("Asset/Image/EditScene/select_border.png"));
	borderMap->initailize();

	mSelectorBoard = std::make_shared<Actor>(mScene);
	mSelectorBoard->setPosition(Vector3(-10000.0f, 0.0f, 0.0f));
	mSelectorBoard->setScale(2.5f);
	mSelectorBoard->initailize();
	auto borderBoard = std::make_shared<SpriteComponent>(mSelectorBoard, game->getRenderer(), 600);
	borderBoard->setTexture(game->getRenderer()->getTexture("Asset/Image/EditScene/select_border.png"));
	borderBoard->initailize();
}

void MapEditor::changeTile()
{
	auto index = mSelectBoardIndex.first * 10 + mSelectBoardIndex.second;
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

	mGameMap.lock()->removeTile(mSelectMapIndex.first, mSelectMapIndex.second);
	mGameMap.lock()->addTile(type, mSelectMapIndex.first, mSelectMapIndex.second, 0);
}

void MapEditor::rotateTile()
{
	mGameMap.lock()->rotTile(mSelectMapIndex.first, mSelectMapIndex.second);
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
		mSelectMapIndex = 
		{	static_cast<int>((mapUpLeft.z - mClickPos.y) / tileSize), 
			static_cast<int>((mClickPos.x - mapUpLeft.x) / tileSize) };

		auto selectXPos = mapPos.x + mSelectMapIndex.second * tileSize;
		auto selectYPos = mapPos.z - mSelectMapIndex.first * tileSize;
		mSelectorMap->setPosition(Vector3(selectXPos, selectYPos, 0.0f));

		changeTile();
	}
}

void MapEditor::checkLeftBoard()
{
	auto tileSize = 80.0f;

	if (mLeftBoardPos.x < mClickPos.x && mClickPos.x < mLeftBoardPos.x + mLeftBoardTexSize.x &&
		mLeftBoardPos.y > mClickPos.y && mClickPos.y > mLeftBoardPos.y - mLeftBoardTexSize.y)
	{		
		mSelectBoardIndex = 
		{ static_cast<int>((mLeftBoardPos.y - mClickPos.y) / 100.0f),
			static_cast<int>((mClickPos.x - mLeftBoardPos.x) / 100.0f) };

		auto selectXPos = mLeftBoardPos.x + 15 + mSelectBoardIndex.second * (15 + tileSize) + tileSize / 2;
		auto selectYPos = mLeftBoardPos.y - 20 - mSelectBoardIndex.first * (15 + tileSize) - tileSize / 2;
		mSelectorBoard->setPosition(Vector3(selectXPos, selectYPos, 0.0f));
	}
}

void MapEditor::checkRightBoard()
{
	auto tileSize = 80.0f;

	if (mRightBoardPos.x < mClickPos.x && mClickPos.x < mRightBoardPos.x + mRightBoardTexSize.x &&
		mRightBoardPos.y > mClickPos.y && mClickPos.y > mRightBoardPos.y - mRightBoardTexSize.y)
	{
		mSelectBoardIndex =
		{ static_cast<int>((mRightBoardPos.y - mClickPos.y) / 100.0f) + 6,
			static_cast<int>((mClickPos.x - mRightBoardPos.x) / 100.0f) };

		auto selectXPos = mRightBoardPos.x + 15 + mSelectBoardIndex.second * (15 + tileSize) + tileSize / 2;
		auto selectYPos = mRightBoardPos.y - 20 - (mSelectBoardIndex.first - 6) * (15 + tileSize) - tileSize / 2;
		mSelectorBoard->setPosition(Vector3(selectXPos, selectYPos, 0.0f));
	}
}