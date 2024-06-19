#include <iostream>
#include "Game.h"

Game::Game()
{
	// Begin without buttons pressed (false)
	w_was_pressed = 0;
	a_was_pressed = 0;
	s_was_pressed = 0;
	d_was_pressed = 0;

	// Begin in menu (true)
	in_menu = 0;

	// Begin in menu 0
	menu_tree = 0;

	is_running = true;

	renderer = nullptr;
	window = nullptr;

	player.is_active = false;

	// Default Colours
	WHITE.r = 255;
	WHITE.b = 255;
	WHITE.g = 255;
	WHITE.a = 255;

	HEALTH_BAR_COLOUR.r = 255;
	HEALTH_BAR_COLOUR.b = 255;
	HEALTH_BAR_COLOUR.g = 255;
	HEALTH_BAR_COLOUR.a = 255;

	BACKGROUND_COLOUR.r = 30;
	BACKGROUND_COLOUR.g = 30;
	BACKGROUND_COLOUR.b = 30;
	BACKGROUND_COLOUR.a = 255;

	// CUBE & HEALTH BAR SIZE
	CUBE_SIZE = 20;
	HEALTH_BAR_THICKNESS = 5;

	// BOUNDS BOX
	BOUNDS_TOP = 50;
	BOUNDS_BOTTOM = 550;
	BOUNDS_LEFT = 50;
	BOUNDS_RIGHT = 1150;

	debug_row.position.x = BOUNDS_RIGHT;
	debug_row.position.y = BOUNDS_TOP;
	debug_row.bullet_velocity.x = -2;
	debug_row.bullet_velocity.y = 0;

	projectile_speed = 2.0f;
	last_shot_tick = 0;
	player_gun_cooldown_seconds = 1;

	BULLET_SIZE = 5;
	BULLET_RANGE = 1000;
};

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

void Game::RunLoop()
{
	while (is_running)
	{
		HandleInputs();

		if (in_menu)
		{
			UpdateMenu();
			DrawMenu();
		}
		else
		{
			if (!player.is_active) { InitialisePlayer(); }
			UpdateGame();
			DrawGame();
		}
	}
};

bool Game::HandleInputs()
{
	bool button_detected = false;

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		// Fönstret stängs
		case SDL_QUIT:
			is_running = false;
			break;
		}
	}

	// Get keyboard input
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_W])
	{
		w_was_pressed = true;
		button_detected = true;
	}
	if (state[SDL_SCANCODE_A])
	{
		a_was_pressed = true;
		button_detected = true;
	}
	if (state[SDL_SCANCODE_S])
	{
		s_was_pressed = true;
		button_detected = true;
	}
	if (state[SDL_SCANCODE_D])
	{
		d_was_pressed = true;
		button_detected = true;
	}
	if (state[SDL_SCANCODE_SPACE])
	{
		space_was_pressed = true;
		button_detected = true;
	}

	return button_detected;
}

void Game::UpdateMenu()
{
	if (menu_tree == 0)
	{
		menu_options[0, 1, 2, 3] = "Next Level", "All Levels", "Leaderboard", "Quit";
	}
};

void Game::DrawMenu()
{

};

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_passed + 16)); // Wait until 16 ms (60fps) has elapsed

	float delta_time = (SDL_GetTicks() - ticks_passed) / 1000.0f;

	if (delta_time > 0.05f)
	{
		delta_time = 0.05f;
	}

	ticks_passed = SDL_GetTicks();

	DetectHits();

	if (w_was_pressed)
	{
		player.position.y -= 2;
		w_was_pressed = false;
		
		if (player.position.y < BOUNDS_TOP) { player.position.y = BOUNDS_TOP; }
	}
	if (s_was_pressed)
	{
		player.position.y += 2;
		s_was_pressed = false;

		if (player.position.y > BOUNDS_BOTTOM) { player.position.y = BOUNDS_BOTTOM; }
	}
	if (space_was_pressed)
	{
		// Check if 2 seconds has passed since the last shot was fired
		if (ticks_passed > (last_shot_tick + 1000 * player_gun_cooldown_seconds))
		{
			xy_vector new_bullet_position = player.position;
			new_bullet_position.x += CUBE_SIZE / 2;
			xy_vector new_bullet_velocity;
			new_bullet_velocity.x = 2;
			new_bullet_velocity.y = 0;

			AddBulletToList
			(
				new_bullet_position,
				new_bullet_velocity,
				true
			);

			// Loop through bullet array until a bullet that is inactive is found
			for (int i = 0; i < 200; i++)
			{
				// If the bullet isn't in use
				if (!bullets[i].is_active)
				{
					// Generate bullet
					bullets[i].is_active = true;
					bullets[i].position.x = player.position.x + CUBE_SIZE / 2;
					bullets[i].position.y = player.position.y;
					bullets[i].velocity.x = 2 * projectile_speed;
					bullets[i].velocity.y = 0;
					bullets[i].can_hit_invaders = true;
					bullets[i].can_hit_player = false;
					bullets[i].range = BULLET_RANGE;
					bullets[i].travel_distance = 0;
					
					last_shot_tick = ticks_passed;

					// Break out of loop to stop bullet generation
					break;
				}
			}
		}
		space_was_pressed = false;
	}

	for (int i = 0; i < 200; i++)
	{
		if (bullets[i].is_active)
		{
			bullets[i].Update();
		}
	}

	for (int i = 0; i < ROW_AMOUNT; i++)
	{
		debug_row.Update(0.2);
		if (debug_row.is_generating_bullet)
		{
			for (int j = 0; j < 10; j++)
			{
				if (debug_row.invaders[j].life_cube.is_shooting)
				{
					xy_vector new_bullet_position = debug_row.invaders[j].life_cube.position;
					new_bullet_position.x -= CUBE_SIZE / 2;
					AddBulletToList
					(
						new_bullet_position,
						debug_row.invaders[j].life_cube.bullet_velocity,
						false
					);
					debug_row.invaders[j].life_cube.is_shooting = false;
				}
			}
			debug_row.is_generating_bullet = false;
		}
	}

	ActivateBullets();
	
};

void Game::AddBulletToList
(
	xy_vector position, 
	xy_vector velocity, 
	bool from_player
)
{
	for (int i = 0; i < 5; i++)
	{
		if (!bullets_to_activate[i].is_active)
		{
			bullets_to_activate[i].is_active = true;
			bullets_to_activate[i].position = position;
			bullets_to_activate[i].velocity = velocity;
			bullets_to_activate[i].range = 1000;
			bullets_to_activate[i].can_hit_invaders = from_player;
			bullets_to_activate[i].can_hit_player = !from_player;
			break;
		}
	}
}

void Game::ActivateBullets()
{
	int j = 0;
	for (int i = 0; i < 5; i++)
	{
		if (bullets_to_activate[i].is_active)
		{
			for (j; j < 200; j++)
			{
				if (!bullets[j].is_active)
				{
					bullets[j] = bullets_to_activate[i];

					bullets_to_activate[i].is_active = false;

					break;
				}
			}
		}
	}
}

void Game::DetectHits()
{
	// Loop through every bullet
	for (int i = 0; i < 200; i++)
	{
		// Check if bullet is active
		if (bullets[i].is_active) 
		{
			// Loop through Rows (currently debug_row is the only one)
			for (int j = 0; j < 1; j++)
			{
				bool bullet_in_row =
					(
						((bullets[i].position.x + BULLET_SIZE / 2) > (debug_row.position.x - CUBE_SIZE / 2)) &&
						((bullets[i].position.x - BULLET_SIZE / 2) < (debug_row.position.x + CUBE_SIZE / 2))
					);

				if (debug_row.is_active && bullet_in_row)
				{
					for (int k = 0; k < 10; k++)
					{
						bool bullet_in_cube =
							(
								((bullets[i].position.y + BULLET_SIZE / 2) > (debug_row.invaders[k].life_cube.position.y - CUBE_SIZE / 2)) &&
								((bullets[i].position.y - BULLET_SIZE / 2) < (debug_row.invaders[k].life_cube.position.y + CUBE_SIZE / 2))
							);
						// If the bullet is in the cube and the cube is active
						if (bullet_in_cube && debug_row.invaders[k].life_cube.is_active && bullets[i].can_hit_invaders)
						{
							std::cout << "WE HAVE A HIT!" << std::endl;
							bullets[i].is_active = false;
							debug_row.invaders[k].life_cube.IsDestroyedFromHit(3);
						}
					}
				}
			}

		}
	}
}

void Game::DrawGame()
{
	// Empty screen
	SDL_SetRenderDrawColor
	(
		renderer,
		BACKGROUND_COLOUR.r,
		BACKGROUND_COLOUR.g,
		BACKGROUND_COLOUR.b,
		BACKGROUND_COLOUR.a
	);

	SDL_RenderClear
	(
		renderer
	);

	// List life cubes to be rendered
	LifeCube life_cubes_to_render[1000];
	int next_index = 0;

	life_cubes_to_render[next_index++] = player;

	for (Invader invader : debug_row.invaders)
	{
		if (invader.life_cube.is_active)
		{
			life_cubes_to_render[next_index++] = invader.life_cube;
		}
	}

	for (LifeCube cube : life_cubes_to_render)
	{
		if (cube.is_active)
		{

			SDL_SetRenderDrawColor
			(
				renderer,
				cube.colour.r,
				cube.colour.g,
				cube.colour.b,
				cube.colour.a
			);

			SDL_Rect rectangle
			{
				static_cast<int> (cube.position.x - CUBE_SIZE / 2), // x coordinate of rectangle upper left corner
				static_cast<int> (cube.position.y - CUBE_SIZE / 2), // y coordinate of rectangle upper left corner
				CUBE_SIZE, // Width of rectangle
				CUBE_SIZE // Height of rectangle
			};

			SDL_RenderFillRect
			(
				renderer,
				&rectangle
			);

			SDL_SetRenderDrawColor(
				renderer,
				HEALTH_BAR_COLOUR.r,
				HEALTH_BAR_COLOUR.g,
				HEALTH_BAR_COLOUR.b,
				HEALTH_BAR_COLOUR.a
			);

			SDL_Rect life_bar
			{
				static_cast<int> (cube.position.x - CUBE_SIZE / 2),
				static_cast<int> (cube.position.y + CUBE_SIZE / 2 + HEALTH_BAR_THICKNESS),
				static_cast<int> (cube.health_percentage * CUBE_SIZE),
				HEALTH_BAR_THICKNESS
			};

			SDL_RenderFillRect
			(
				renderer,
				&life_bar
			);
		}
	}

	for (Bullet bullet: bullets)
	{
		if (bullet.is_active)
		{
			SDL_SetRenderDrawColor
			(
				renderer,
				255,
				255,
				255,
				255
			);

			SDL_Rect rectangle
			{
				static_cast<int> (bullet.position.x - BULLET_SIZE / 2),
				static_cast<int> (bullet.position.y - BULLET_SIZE / 2),
				BULLET_SIZE,
				BULLET_SIZE
			};

			SDL_RenderFillRect
			(
				renderer,
				&rectangle
			);
		}
	}

	// Present graphics
	SDL_RenderPresent(renderer);
}

void Game::InitialisePlayer()
{
	player.is_active = true;
	player.position.x = BOUNDS_LEFT;
	player.position.y = 300.0f;
	player.total_hitpoints = 10.0f;
	player.hitpoints = 10.0f;
	player.health_percentage = 1.0f;
	player.colour = WHITE;
};

void Game::Terminate()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit;
}