#include <iostream>
#include "Game.h"

int main(int argc, char** argv)
{
	std::cout << "Hello world" << std::endl;

	Game game;

	bool success = game.Initialize();

	game.RunLoop();

	game.Terminate();

	return 0;
}