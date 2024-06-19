#include "Game.h"
#include <iostream>

int main(int argc, char **argv)
{
	std::srand(time(0));

	std::cout << "Gut" << std::endl;

	Game game;

	if (game.Initialise())
	{
		game.RunLoop();
	}

	game.Terminate();

	return 0;
}