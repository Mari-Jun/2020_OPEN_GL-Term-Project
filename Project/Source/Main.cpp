//Main Code
#include "Game/Game.h"

int main(int argc, char** argv)
{
	auto game = std::make_shared<Game>();

	bool success = game->initialize(argc, argv);

	if (success)
	{
		game->run();
	}

	game->shutDown();

	return 0;
}
