#include <fstream>
#include <iostream>

#include "Game.h"
#include "Leaderboard.h"

/* 
The game is initialised in the main loop below which functions as a menu in the
console, as rendering text in SDL is a hassle. The SDL window is not created
until a level is chosen. And afterwards it is automatically terminated, which
returns the player to the console, and the menu.

The main game mechanics are located in Game.h & Game.cpp

The Structs.h file configures structs such as xy_vectors used in the rest of
the game. 

The Invader.h & Invader.cpp configures the invaders. Classes Row and Invader
are located here.

The LifeCube.h & LifeCube.cpp files configure the cubes of both the invaders 
and the player. These are used by both the DrawGame function as well as hitbox 
calculations, both of which are in the Game class. They also configure their own
bullets.

The Bullet.h & Bullet.cpp files configure bullets which are currently the only
weapons in the game. They are used by the DrawGame function as well as hitbox
calculations.
*/

int main(int argc, char** argv)
{
	Leaderboard leaderboard;

	Game game;

	int score{};
	bool has_won{};

	int CONFIGURED_LEVELS_COUNT = 2;

	std::cout << "SPACE INVADERS v0.0.3" << std::endl;

	while (true)
	{
		// READING SCORES
		leaderboard.Read();

		// Main menu

		std::cout << "Please make a choice below:" << std::endl;
		std::cout << "[1] Select Level" << std::endl;
		std::cout << "[0] Display leaderboard" << std::endl;

		int user_input{};

		// The following code snippet catches type errors and resets the cin function.
		while (!(std::cin >> user_input) || (user_input < 0) || (user_input > 1))
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Invalid input" << std::endl;
		}

		switch (user_input)
		{

		case 0:

			leaderboard.Display();

			break;

		case 1:

			std::cout << "Please select level, from 1 to " << CONFIGURED_LEVELS_COUNT << std::endl;
			std::cout << "[0] Go back" << std::endl;

			// The following code snippet catches type errors and resets the cin function.
			while (!(std::cin >> user_input) || (user_input < 0) || (user_input > CONFIGURED_LEVELS_COUNT))
			{
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "Invalid input" << std::endl;
			}

			if (user_input == 0) { break; }

			if (game.InitialiseLevel(user_input))
			{
				std::cout << "Level initialised" << std::endl;
			}

			if (game.Initialise())
			{
				score = game.RunLoop();
				has_won = game.has_won;
			}

			game.Terminate();

			if (has_won)
			{
				std::cout << "Level completed!" << std::endl;
			}

			std::cout << "Score: " << score << std::endl;

			int placing = leaderboard.Update(score);

			if (placing != 0)
			{
				std::cout << "Congratulation, you are in place " << placing << "on the leaderboard" << std::endl;
			}

			break;

		}
		leaderboard.Write();
	}



	/*
	std::srand(time(0));

	std::cout << "Gut" << std::endl;

	Game game;

	if (game.Initialise())
	{
		game.RunLoop();
	}

	game.Terminate();
	*/

	return 0;
}

