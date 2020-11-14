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
	Vector2 mClickPos;
	std::pair<int, int> mSelectTileIndex;
	bool mIsSelectTile;
};