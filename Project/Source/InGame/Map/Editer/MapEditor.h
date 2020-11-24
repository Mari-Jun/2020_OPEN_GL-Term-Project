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

class MapEditor
{
public:
	MapEditor(const std::weak_ptr<class Scene>& scene);
	~MapEditor() noexcept;

	void editInput();
	void loadData();

	void setGameMap(const std::weak_ptr<class GameMap>& gameMap);
	void setBoard(const std::string& type, const Vector2& pos, const Vector2& size);

private:
	std::weak_ptr<class Scene> mScene;
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

	Board mLeftBoard;
	Board mRightBoard;
	Board mTimeBoard;
};