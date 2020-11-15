#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "../../../Game/Math/Math.h"


class MapEditor
{
public:
	MapEditor(const std::weak_ptr<class Game>& game, const std::weak_ptr<class GameMap>& gameMap);
	~MapEditor() noexcept;

	void editInput();

	void loadData();

private:
	std::weak_ptr<class Game> mGame;
	std::weak_ptr<class GameMap> mGameMap;
	std::string mFileName;
	Vector2 mClickPos;

private:
	void changeTile();
	void rotateTile();
	void changeStartTile();
	void changeEndTile();

	void checkTileIndex();
	void checkLeftBoard();
	void checkRightBoard();

private:
	//Map selector
	std::shared_ptr<class Actor> mSelectorMap;
	std::pair<int, int> mSelectMapIndex;
	
	//Board selector
	static constexpr std::pair<int, int> mBoardMaxIndex = { 11, 3 };
	std::shared_ptr<class Actor> mSelectorBoard;
	std::pair<int, int> mSelectBoardIndex;
	Vector2 mLeftBoardPos;
	Vector2 mLeftBoardTexSize;
	Vector2 mRightBoardPos;
	Vector2 mRightBoardTexSize;

public:
	void setLeftBoardPos(const Vector2& pos) { mLeftBoardPos = pos; }
	void setLeftBoardTexSize(const Vector2& size) { mLeftBoardTexSize = size; }
	void setRightBoardPos(const Vector2& pos) { mRightBoardPos = pos; }
	void setRightBoardTexSize(const Vector2& size) { mRightBoardTexSize = size; }
};