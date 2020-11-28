#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "../../../Game/Math/Math.h"

struct Board
{
	Vector2 mPos;
	Vector2 mSize;
};

struct Selector
{
	std::shared_ptr<class Actor> mSelector;
	std::pair<int, int> mIndex;
};

class MapEditor
{
public:
	MapEditor(const std::weak_ptr<class EditScene>& scene);
	~MapEditor() noexcept;

	bool saveMap();
	void newMap();

	void editInput();
	void loadData();

	void setGameMap(const std::weak_ptr<class GameMap>& gameMap);
	void setBoard(const std::string& type, const Vector2& pos, const Vector2& size);

private:
	std::weak_ptr<class EditScene> mEditScene;
	std::weak_ptr<class GameMap> mGameMap;
	Vector2 mClickPos;

private:
	void changeTile();
	void rotateTile();
	void changeStartTile();
	void changeEndTile();
	void changeTime();

	void checkTileIndex();
	void checkBoard();
	void checkTime();

private:
	static constexpr std::pair<int, int> mBoardMaxIndex = { 11, 3 };
	static constexpr std::pair<int, int> mTimeMaxIndex = { 2, 3 };
	Selector mMapSelector;
	Selector mBoardSelector;
	Selector mTimeSelector;

	Board mLeftBoard;
	Board mRightBoard;
	Board mTimeBoard;
};