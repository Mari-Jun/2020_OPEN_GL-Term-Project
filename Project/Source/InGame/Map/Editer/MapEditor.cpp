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
	, mSelectMapIndex({ -1,-1 })
	, mSelectBoardIndex({ -1,-1 })
	, mLeftBoardPos(Vector2::Zero)
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
		checkLeftBoard();
	}

	if (game->getKeyBoard()->isSpecialKeyPressed(GLUT_KEY_END))
	{
		mGameMap.lock()->saveMap();
	}
}

void MapEditor::loadData()
{
	mSelectorMap = std::make_shared<Actor>(mGame);
	mSelectorMap->initailize();
	auto borderMap = std::make_shared<SpriteComponent>(mSelectorMap, mGame.lock()->getRenderer());
	borderMap->setTexture(mGame.lock()->getRenderer()->getTexture("Asset/Image/EditScene/select_border.png"));
	borderMap->initailize();

	mSelectorBoard = std::make_shared<Actor>(mGame);
	mSelectorBoard->setPosition(Vector3(-10000.0f, 0.0f, 0.0f));
	mSelectorBoard->setScale(2.5f);
	mSelectorBoard->initailize();
	auto borderBoard = std::make_shared<SpriteComponent>(mSelectorBoard, mGame.lock()->getRenderer(), 6000);
	borderBoard->setTexture(mGame.lock()->getRenderer()->getTexture("Asset/Image/EditScene/select_border.png"));
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
	case 30: type = "StartPoint"; break;
	case 31: type = "EndPoint"; break;
	case 32: type = "SnowBasic"; break;
	case 40: type = "SnowRock"; break;
	case 41: type = "SnowHill"; break;
	case 42: type = "SnowCrystal"; break;
	case 50: type = "SnowTree"; break;
	case 51: type = "SnowTreeDouble"; break;
	case 52: type = "SnowTreeQuad"; break;
	default:
		return;
	}

	mGameMap.lock()->removeTile(mSelectMapIndex.first, mSelectMapIndex.second);
	mGameMap.lock()->addTile(type, mSelectMapIndex.first, mSelectMapIndex.second, 0);
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

		if (mSelectBoardIndex.first >= 0 && mSelectBoardIndex.first < mBoardMaxIndex.first &&
			mSelectBoardIndex.second >= 0 && mSelectBoardIndex.second < mBoardMaxIndex.second)
		{
			changeTile();
		}
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