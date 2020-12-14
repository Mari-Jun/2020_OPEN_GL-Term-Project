#include <filesystem>
#include <fstream>
#include <sstream>
#include "MapEditor.h"
#include "../GameMap.h"
#include "../../Scene/EditScene.h"
#include "../../../Game/Graphics/Window.h"
#include "../../../Game/Game.h"
#include "../../Actor/Tile/Tile.h"
#include "../../../Game/Input/KeyBoard.h"
#include "../../../Game/Input/Mouse.h"
#include "../../../Game/Graphics/Mesh/SpriteComponent.h"


MapEditor::MapEditor(const std::weak_ptr<class EditScene>& scene)
	: mEditScene(scene)
	, mMapSelector({ nullptr, {10, 10} })
	, mBoardSelector({ nullptr, {-1, -1 } })
	, mTimeSelector({ nullptr, {0, 0} })
	, mSeasonSelector({ nullptr, {0, 0} })
{
	loadData();
}

MapEditor::~MapEditor()
{
	mMapSelector.mSelector->setState(Actor::State::Dead);
	mBoardSelector.mSelector->setState(Actor::State::Dead);
	mTimeSelector.mSelector->setState(Actor::State::Dead);
	mSeasonSelector.mSelector->setState(Actor::State::Dead);
}

bool MapEditor::saveMap()
{
	auto map = mGameMap.lock();
	const auto& fileName = map->getFileName();
	if (fileName.size() != 0)
	{
		//Open Obj file
		std::ofstream mapFile(fileName);
	

		if (!mapFile.is_open())
		{
			std::cerr << "file not found : " << fileName << '\n';
			return false;
		}

		unsigned int y = 0;
		const auto& tile = map->getTiles();

		mapFile << "Time " << map->getTime() << '\n';
		mapFile << "Season " << map->getSeason() << '\n';

		for (auto y = 0; y < tile.size(); y++)
		{
			mapFile << "Line " << y + 1 << " " << tile.size() << '\n';
			mapFile << "Type ";
			for (const auto& x : tile[y])
			{
				auto rot = round(Math::ToDegrees(Math::Acos(Quaternion::Dot(Quaternion(Vector3::UnitY, 0), x.lock()->getRotation()))));
				mapFile << x.lock()->getTileTypeToString() << ' ' << rot * 2 << ' ';
			}
			mapFile << '\n';
		}

		mapFile << "Minion " << map->getMinionCount() << '\n';

		std::cerr << fileName << " Save complete\n";
		return true;
	}
	return false;
}

int MapEditor::newMap()
{
	auto stage = 0;
	while (++stage)
	{
		std::string fileName = "Asset/Map/Stage";
		fileName += std::to_string(stage) + ".txt";

		std::ifstream mapFile(fileName);

		if (!mapFile.is_open())
		{
			std::ofstream mapFile(fileName);
			unsigned int y = 0;
			auto map = mGameMap.lock();
			const auto& tile = map->getTiles();

			mapFile << "Time " << "Sunny" << '\n';
			mapFile << "Season " << "Green" << '\n';

			for (auto y = 0; y < tile.size(); y++)
			{
				mapFile << "Line " << y + 1 << " " << tile.size() << '\n';
				mapFile << "Type ";
				for (const auto& x : tile[y])
				{
					mapFile << "Basic" << ' ' << 0 << ' ';
				}
				mapFile << '\n';
			}

			mapFile << "Minion " << 1 << '\n';

			std::cerr << "Create new file : " << fileName << " complete\n";
			return stage;
		}
	}
	return 0;
}

int MapEditor::deleteMap()
{
	auto map = mGameMap.lock();
	auto stage = mEditScene.lock()->getStage();
	std::string fileName = "Asset/Map/Stage" + std::to_string(stage) + ".txt";
	std::string fileNameNext = "Asset/Map/Stage" + std::to_string(stage + 1) + ".txt";

	std::filesystem::path p1(fileName);
	std::filesystem::path p2(fileNameNext);
	
	if (std::filesystem::exists(p1))
	{
		auto next = false;
		while (std::filesystem::exists(p2))
		{
			next = true;
			std::filesystem::copy_file(p2, p1, std::filesystem::copy_options::overwrite_existing);
			stage++;
			fileName = "Asset/Map/Stage" + std::to_string(stage) + ".txt";
			fileNameNext = "Asset/Map/Stage" + std::to_string(stage + 1) + ".txt";

			p1 = fileName;
			p2 = fileNameNext;
		}
		std::filesystem::remove(p1);
		return mEditScene.lock()->getStage() - (1 - next);
	}
	
	return stage;
}

void MapEditor::editInput()
{
	auto game = mEditScene.lock()->getGame().lock();

	if (game->getMouse()->getState(GLUT_RIGHT_BUTTON))
	{
		mClickPos = game->getMouse()->getPosition();
		checkTileIndex();
		checkBoard(mLeftBoard, mBoardSelector);
		checkBoard(mRightBoard, mBoardSelector, true);
		if (checkBoard(mTimeBoard, mTimeSelector) || checkBoard(mSeasonBoard, mSeasonSelector))
		{
			changeTimeSeason();
		}
	}
	if (game->getKeyBoard()->isKeyFirst('r'))
	{
		rotateTile();
	}
}

void MapEditor::loadData()
{
	setSelector(mMapSelector, Vector3::Zero, 1.0f);
	setSelector(mBoardSelector, Vector3(-10000.0f, 0.0f, 0.0f), 2.5f);
	setSelector(mTimeSelector, Vector3(-10000.0f, 0.0f, 0.0f), 2.5f);
	setSelector(mSeasonSelector, Vector3(-10000.0f, 0.0f, 0.0f), 2.5f);
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
	else if (type == "Time")
	{
		mTimeBoard.mPos = pos;
		mTimeBoard.mSize = size;
	}
	else
	{
		mSeasonBoard.mPos = pos;
		mSeasonBoard.mSize = size;
	}
}

void MapEditor::setSelector(Selector& selector, Vector3 pos, float scale)
{
	auto game = mEditScene.lock()->getGame().lock();
	selector.mSelector = std::make_shared<Actor>(mEditScene);
	selector.mSelector->setPosition(pos);
	selector.mSelector->setScale(scale);
	selector.mSelector->initailize();
	auto borderBoard = std::make_shared<SpriteComponent>(selector.mSelector, game->getRenderer(), 600);
	borderBoard->setTexture(game->getRenderer()->getTexture("Asset/Image/EditScene/select_border.png"));
	borderBoard->initailize();
}

void MapEditor::changeTile()
{
	auto index = mBoardSelector.mIndex.first * 10 + mBoardSelector.mIndex.second;
	auto type = "";
	switch (index)
	{
	case 0: type = "Road"; break;
	case 1: type = "Basic"; break;
	case 2: type = "Light"; break;
	case 10: type = "Rock"; break;
	case 11: type = "Hill"; break;
	case 12: type = "Crystal"; break;
	case 20: type = "Tree"; break;
	case 21: type = "TreeDouble"; break;
	case 22: type = "TreeQuad"; break;
	case 30: type = "StartPoint"; changeStartTile(); break;
	case 31: type = "EndPoint"; changeEndTile(); break;
	case 40: type = "TowerRoundA"; break;
	case 41: type = "TowerRoundC"; break;
	case 42: type = "TowerBlaster"; break;
	case 50: type = "TowerSquareA"; break;
	case 51: type = "TowerSquareB"; break;
	case 52: type = "TowerSquareC"; break;
	case 60: type = "TowerBallista"; break;
	case 61: type = "TowerCannon"; break;
	case 62: type = "TowerCatapult"; break;
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

void MapEditor::changeTimeSeason()
{
	auto index = mTimeSelector.mIndex.first * 10 + mTimeSelector.mIndex.second;
	auto timeType = "";
	switch (index)
	{
	case 0: timeType = "Sunny"; break;
	case 1: timeType = "Sunset"; break;
	case 2: timeType = "Moon"; break;
	default: break;
	}

	index = mSeasonSelector.mIndex.first * 10 + mSeasonSelector.mIndex.second;
	auto seasonType = "";
	switch (index)
	{
	case 0: seasonType = "Sakura"; break;
	case 1: seasonType = "Green"; break;
	case 10: seasonType = "Maple"; break;
	case 11: seasonType = "Snow"; break;
	default: break;
	}
	
	mEditScene.lock()->loadGameMap(timeType, seasonType);
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

bool MapEditor::checkBoard(Board& board, Selector& selector, bool right)
{
	auto tileSize = 80.0f;

	if (board.mPos.x < mClickPos.x && mClickPos.x < board.mPos.x + board.mSize.x &&
		board.mPos.y > mClickPos.y && mClickPos.y > board.mPos.y - board.mSize.y)
	{		
		selector.mIndex = 
		{ static_cast<int>((board.mPos.y - mClickPos.y) / 100.0f) + right * 4,
			static_cast<int>((mClickPos.x - board.mPos.x) / 100.0f) };

		auto selectXPos = board.mPos.x + 15 + selector.mIndex.second * (15 + tileSize) + tileSize / 2;
		auto selectYPos = board.mPos.y - 20 - (selector.mIndex.first - right * 4) * (15 + tileSize) - tileSize / 2;
		selector.mSelector->setPosition(Vector3(selectXPos, selectYPos, 0.0f));

		return true;
	}

	return false;
}