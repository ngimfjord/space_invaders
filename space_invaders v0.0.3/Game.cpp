#include <iostream>

#include "Game.h"

Game::Game() {};

bool Game::Initialise()
{

	// Initialize SDL
	int sdl_result = SDL_Init(SDL_INIT_VIDEO);

	if (sdl_result != 0)
	{
		SDL_Log("Unable to initialize SDL %s", SDL_GetError());
		return false;
	}

	// Create SDL window

	window = SDL_CreateWindow(
		"SPACE INVADERS",
		50, // The x-coordinate of the upper left corner of the created window
		50, // The y-coordinate of the upper left corner of the created window
		1200, // Width of window
		600, // Height of window
		0 // No flags (fullscreen etc)
	);

	if (!window)
	{
		SDL_Log("Unable to create window %s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED
	);

	return true;

};

bool Game::InitialiseLevel(int n)
{
	level_progression_pixels = 0.0f;
	score = 0;

	ticks_at_start = SDL_GetTicks();

	// Loop through every structure
	for (int i = 0; i < 20; i++)
	{
		// Clear the structure, deactivate any cubes and rows
		invader_structures[i].Clear();
	}

	switch (n)
	{
	case 1:

		// Darkish gray
		background_colour.Set(30, 30, 30, 255);

		// White
		cube_colour.Set(255, 255, 255, 255);
		bullet_colour.Set(255, 255, 255, 255);

		// Wine-y red
		health_bar_colour.Set(130, 0, 61, 255);

		level_progression_per_frame = 0.2f;
		player.current_health = player.initial_health = 20;
		cooldown_ms = 1000;

		// The game only loops through the 2 first structures
		amount_of_structures = 3;

		// Create two identical structures
		for (int i = 0; i < (amount_of_structures); i++)
		{
			
			/*
			The below lines create a structure that looks like this:
					    FRONT			ROW
							XX			0
						   X  X			1
						  X    X		2
						 X      X		3
						X X    X X		4
						BACK
			*/

			invader_structures[i].rows[0].is_active = true;
			invader_structures[i].rows[0].invaders[4].Activate(5);
			invader_structures[i].rows[0].invaders[5].Activate(5);

			invader_structures[i].rows[1].is_active = true;
			invader_structures[i].rows[1].invaders[3].Activate(5);
			invader_structures[i].rows[1].invaders[6].Activate(5);

			invader_structures[i].rows[2].is_active = true;
			invader_structures[i].rows[2].invaders[2].Activate(5);
			invader_structures[i].rows[2].invaders[7].Activate(5);

			invader_structures[i].rows[3].is_active = true;
			invader_structures[i].rows[3].invaders[1].Activate(5);
			invader_structures[i].rows[3].invaders[8].Activate(5);

			invader_structures[i].rows[4].is_active = true;
			invader_structures[i].rows[4].invaders[0].Activate(5);
			invader_structures[i].rows[4].invaders[2].Activate(5);
			invader_structures[i].rows[4].invaders[7].Activate(5);
			invader_structures[i].rows[4].invaders[9].Activate(5);

			// The structure should only loop through and generate the first five rows.
			invader_structures[i].rows_in_structure = 5;

			// The rows in the structure are separated by 40 pixels.
			invader_structures[i].space_between_rows = 40;

			// The dimensions of the structure are 360 in height (y) and 160 in length/width (x).
			invader_structures[i].height_in_pixels = 360;
			invader_structures[i].width_in_pixels = 160;

			// Set 100 pixels between the structures.
			space_between_structures[i] = 350;

			// Set the y-speed to 0.3 pixels per frame.
			invader_structures[i].y_pixels_per_frame = 0.3f;

			// Set the initial health of the cubes
			invader_structures[i].health_of_cubes = 5;
			invader_structures[i].InitialiseCubeHealth();

		}

		// Set the initial positions
		SetPositions();

		// Return true - initialisation successful
		return true;

	case 2:

		// Darkish gray
		background_colour.Set(30, 30, 30, 255);

		// White
		cube_colour.Set(255, 255, 255, 255);
		bullet_colour.Set(255, 255, 255, 255);

		// Wine-y red
		health_bar_colour.Set(130, 0, 61, 255);

		level_progression_per_frame = 0.3f;
		player.current_health = player.initial_health = 20;
		cooldown_ms = 900;

		amount_of_structures = 5;

		// Create two identical structures
		for (int i = 0; i < (amount_of_structures); i++)
		{

			/*
			The below lines create a structure that looks like this:
						FRONT			ROW
						X X XX X X		0
						 X X  X	X		1
						X X    X X		2
						 X      X		3
						X X    X X		4
						BACK
			*/

			invader_structures[i].rows[0].is_active = true;
			invader_structures[i].rows[0].invaders[0].Activate(5);
			invader_structures[i].rows[0].invaders[2].Activate(5);
			invader_structures[i].rows[0].invaders[4].Activate(5);
			invader_structures[i].rows[0].invaders[5].Activate(5);
			invader_structures[i].rows[0].invaders[7].Activate(5);
			invader_structures[i].rows[0].invaders[9].Activate(5);

			invader_structures[i].rows[1].is_active = true;
			invader_structures[i].rows[1].invaders[1].Activate(5);
			invader_structures[i].rows[1].invaders[3].Activate(5);
			invader_structures[i].rows[1].invaders[6].Activate(5);
			invader_structures[i].rows[1].invaders[8].Activate(5);

			invader_structures[i].rows[2].is_active = true;
			invader_structures[i].rows[2].invaders[0].Activate(5);
			invader_structures[i].rows[2].invaders[2].Activate(5);
			invader_structures[i].rows[2].invaders[7].Activate(5);
			invader_structures[i].rows[2].invaders[9].Activate(5);

			invader_structures[i].rows[3].is_active = true;
			invader_structures[i].rows[3].invaders[1].Activate(5);
			invader_structures[i].rows[3].invaders[8].Activate(5);

			invader_structures[i].rows[4].is_active = true;
			invader_structures[i].rows[4].invaders[0].Activate(5);
			invader_structures[i].rows[4].invaders[2].Activate(5);
			invader_structures[i].rows[4].invaders[7].Activate(5);
			invader_structures[i].rows[4].invaders[9].Activate(5);

			// The structure should only loop through and generate the first five rows.
			invader_structures[i].rows_in_structure = 5;

			// The rows in the structure are separated by 40 pixels.
			invader_structures[i].space_between_rows = 40;

			// The dimensions of the structure are 360 in height (y) and 160 in length/width (x).
			invader_structures[i].height_in_pixels = 360;
			invader_structures[i].width_in_pixels = 160;

			// Set 100 pixels between the structures.
			space_between_structures[i] = 350;

			// Set the y-speed to 0.3 pixels per frame.
			invader_structures[i].y_pixels_per_frame = 0.4f;

			// Set the initial health of the cubes
			invader_structures[i].health_of_cubes = 5;
			invader_structures[i].InitialiseCubeHealth();

		}

		// Set the initial positions
		SetPositions();

		// Return true - initialisation successful
		return true;

	default:
		return false;
	}
};

int Game::RunLoop() 
{
	is_running = true;
	is_paused = false;

	while (is_running)
	{

		ControlFramerate();
		ProcessInput();

		if (!is_paused)
		{
			UpdateGame();
			CheckBulletCollissions();
			CheckLosingConditions();
			DrawGame();
		}
	}

	return score;
};

void Game::SetPositions()
{
	player.position.x = 50;
	player.position.y = 300;
	player.is_player = true;
	player.is_invader = false;
	player.is_shooting = true;
	player.velocity_of_created_bullets.x = 6;
	int space = 0;

	for (int i = 0; i < 20; i++)
	{
		invader_structures[i].initial_x = 1000 + space;
		space += invader_structures[i].width_in_pixels + space_between_structures[i];
	}
}

void Game::ControlFramerate()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_passed + 16)); // Wait until 16 ms (60fps) has elapsed

	float delta_time = (SDL_GetTicks() - ticks_passed) / 1000.0f;

	if (delta_time > 0.05f)
	{
		delta_time = 0.05f;
	}

	ticks_passed = SDL_GetTicks();
};

void Game::ProcessInput()
{

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			// Fönstret stängs
			is_running = false;
			break;
		}
	}

	// Get keyboard input
	const Uint8* state = SDL_GetKeyboardState(NULL);

	w_is_being_pressed = false;
	if (state[SDL_SCANCODE_W])
	{
		w_is_being_pressed = true;
	}
	s_is_being_pressed = false;
	if (state[SDL_SCANCODE_S])
	{
		s_is_being_pressed = true;
	}
	space_is_being_pressed = false;
	if (state[SDL_SCANCODE_SPACE])
	{
		space_is_being_pressed = true;
	}
	if (state[SDL_SCANCODE_ESCAPE])
	{
		escape_is_being_pressed = true;

		/*
		To ensure the game isn't immediately unpaused because the escape button
		is still being pressed in the next frame, the game waits for 100 ms.
		*/

		while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_passed + 100));
		is_paused = !is_paused;
	}
};

void Game::UpdateGame()
{
	UpdatePlayer();
	UpdateInvaders();
	UpdateBullets();
};

void Game::DrawGame()
{
	// Draw the game

	DrawBackground();

	DrawLifeCubes();

	DrawBullets();

	SDL_RenderPresent(renderer);
};

void Game::UpdatePlayer()
{
	player.position.x = 50;
	if (w_is_being_pressed)
	{
		player.position.y -= 2;
		if (player.position.y < 50)
		{
			player.position.y = 50;
		}
	}
	if (s_is_being_pressed)
	{
		player.position.y += 2;
		if (player.position.y > 550)
		{
			player.position.y = 550;
		}
	}
	player.position_of_created_bullets = player.position;
	player.position_of_created_bullets.x += 12;
	if (space_is_being_pressed && (ticks_passed > (last_shot_ticks + cooldown_ms)))
	{
		player.is_shooting = true;
	}
	if (player.is_shooting)
	{
		CreateBullet(player.position_of_created_bullets, player.velocity_of_created_bullets, false, true);
		player.is_shooting = false;
		last_shot_ticks = ticks_passed;
	}
}

void Game::UpdateInvaders()
{
	level_progression_pixels += level_progression_per_frame;
	// Loop through every structure and update its position
	for (int i = 0; i < amount_of_structures; i++)
	{
		invader_structures[i].Update(level_progression_pixels);
	}
}

void Game::UpdateBullets()
{
	for (int i = 0; i < 200; i++)
	{
		if (bullets[i].is_active)
		{
			bullets[i].UpdatePosition();
		}
	}
}

void Game::CheckBulletCollissions()
{
	// Loop through each bullet
	for (int b = 0; b < 200; b++)
	{
		for (int s = 0; s < amount_of_structures; s++)
		{
			for (int r = 0; r < 12; r++)
			{
				for (int i = 0; i < 10; i++)
				{
					bool collided =
						(
							(bullets[b].position.x - 2) < (invader_structures[s].rows[r].invaders[i].position.x + 10) &&
							(bullets[b].position.x + 2) > (invader_structures[s].rows[r].invaders[i].position.x - 10) &&
							(bullets[b].position.y - 2) < (invader_structures[s].rows[r].invaders[i].position.y + 10) &&
							(bullets[b].position.y + 2) > (invader_structures[s].rows[r].invaders[i].position.y - 10) &&
							invader_structures[s].rows[r].invaders[i].is_active &&
							bullets[b].is_active
						);

					bool can_hit =
						(
							(bullets[b].can_hit_invaders && invader_structures[s].rows[r].invaders[i].is_invader) ||
							(bullets[b].can_hit_player && invader_structures[s].rows[r].invaders[i].is_player)
						);

					if (collided && can_hit)
					{
						std::cout << "Hit detected" << std::endl;
						bullets[b].is_active = false;
						if (invader_structures[s].rows[r].invaders[i].IsDestroyed(3.0f))
						{
							score += invader_structures[s].rows[r].invaders[i].initial_health;
						};
					}

				}
			}
		}
	}
}

void Game::CheckLosingConditions()
{
	bool any_cubes = false;

	for (InvaderStructure structure : invader_structures)
	{
		for (Row row : structure.rows)
		{
			for (LifeCube invader : row.invaders)
			{
				if (invader.is_active)
				{
					any_cubes = true;
					if (invader.position.x < 100 && (ticks_passed - ticks_at_start) > 2000)
					{
						has_won = false;
						is_running = false;
					}
				}
			}
		}
	}

	if (!any_cubes)
	{
		has_won = true;
		is_running = true;
	}
};

void Game::DrawBackground()
{
	SetDrawingColour(background_colour);
	SDL_RenderClear(renderer);
}

void Game::DrawLifeCubes()
{
	/*
	This function draws the cubes onto the screen. This includes the player cube
	as well as the invader cubes.
	*/

	int CUBE_SIZE = 20;

	SetDrawingColour(cube_colour);

	// Draw the player
	SDL_Rect rectangle
	{
		static_cast<int> (player.position.x - CUBE_SIZE / 2),
		static_cast<int> (player.position.y - CUBE_SIZE / 2),
		CUBE_SIZE,
		CUBE_SIZE
	};

	SDL_RenderFillRect
	(
		renderer,
		&rectangle
	);

	/*
	This loops through the structures. Since we are only reading data, namely
	its coordinates, we can use a range based loop, which clarifies which data
	is read.
	*/
	int i = 0;

	for (InvaderStructure invader_structure:invader_structures)
	{
		// Breaks after rendering all the structures
		if (i++ >= amount_of_structures)
		{
			break;
		}

		int j = 0;

		// Loops through the rows in the structures
		for (Row row : invader_structure.rows)
		{
			// Breaks after rendering all the rows
			if (j++ >= invader_structure.rows_in_structure || !row.is_active)
			{
				break;
			}

			// Loop through the cubes in the rows
			for (LifeCube cube : row.invaders)
			{

				if (cube.is_active)
				{

					SetDrawingColour(cube_colour);

					SDL_Rect rectangle
					{
						static_cast<int> (cube.position.x - CUBE_SIZE / 2),
						static_cast<int> (cube.position.y - CUBE_SIZE / 2),
						CUBE_SIZE,
						CUBE_SIZE
					};

					if ((cube.position.x < 100) && ((ticks_passed - ticks_at_start) > 2000))
					{
						is_running = false;
						has_won = false;
					}

					SDL_RenderFillRect
					(
						renderer,
						&rectangle
					);

					SetDrawingColour(health_bar_colour);

					SDL_Rect health_bar
					{
						static_cast<int> (cube.position.x - CUBE_SIZE / 2),
						static_cast<int> (cube.position.y + CUBE_SIZE / 2 + 5),
						static_cast<int> (CUBE_SIZE * cube.current_health / cube.initial_health),
						5
					};

					SDL_RenderFillRect
					(
						renderer,
						&health_bar
					);
				}
			}
		}
	}
}

void Game::DrawBullets()
{
	SetDrawingColour(bullet_colour);

	for (int i = 0; i < 200; i++)
	{
		if (bullets[i].is_active)
		{
			SDL_Rect bullet
			{
				static_cast <int> (bullets[i].position.x - 2),
				static_cast <int> (bullets[i].position.y - 2),
				4,
				4
			};

			SDL_RenderFillRect
			(
				renderer,
				&bullet
			);
		}
	}
}

void Game::CreateBullet(xy_vector position, xy_vector velocity, bool can_hit_player, bool can_hit_invaders)
{
	for (int i = 0; i < 200; i++)
	{
		if (!bullets[i].is_active)
		{
			bullets[i].is_active = true;
			bullets[i].initial_position = position;
			bullets[i].position = position;
			bullets[i].velocity = velocity;
			bullets[i].can_hit_player = can_hit_player;
			bullets[i].can_hit_invaders = can_hit_invaders;
			return;
		}
	}
}

void Game::Terminate()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit;
}

void Game::SetDrawingColour(Colour colour)
{
	SDL_SetRenderDrawColor
	(
		renderer,
		colour.red,
		colour.green,
		colour.blue,
		colour.alpha
	);
}