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
{
	std::cout << "¤Ð\n";
}

MapEditor::~MapEditor()
{
	std::cout << "¤Ð\n";
}

void MapEditor::editInput()
{
	auto game = mGame.lock();

	if (game->getMouse()->getState(GLUT_LEFT_BUTTON))
	{

	}

}

void MapEditor::loadData()
{

}