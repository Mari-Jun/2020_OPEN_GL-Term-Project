//Main Code
#include <Windows.h>
#include "Game/Game.h"

int main(int argc, char** argv)
{
	HWND hWndConsole = GetConsoleWindow();
	ShowWindow(hWndConsole, SW_SHOW);

	auto game = std::make_shared<Game>();

	bool success = game->initialize(argc, argv);

	if (success)
	{
		game->run();
	}

	game->shutDown();

	return 0;
}
