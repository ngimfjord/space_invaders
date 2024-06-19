#include "Game.h"
#include "Game.h"
#include <iostream>

Game::Game()
{
	mWindow = nullptr;
	mRenderer = nullptr;
	ticks_passed = 0;
	is_running = true;
	player_pos.x = 50.0f;
	player_pos.y = 300.0f;
	player_movement = 0;

	projectile_cooldown_seconds = 2;
	player_projectile_speed = 2;
	player_projectile_range = 1000;
	last_projectile_ticks = 0;

	projectiles[MAX_PROJECTILES];
};

bool Game::Initialize()
{

	// Initialize SDL
	int sdl_result = SDL_Init(SDL_INIT_VIDEO);

	if (sdl_result != 0)
	{
		SDL_Log("Unable to initialize SDL %s", SDL_GetError());
		return false;
	}

	// Create SDL window

	mWindow = SDL_CreateWindow(
		"SPACE INVADERS",
		50, // The x-coordinate of the upper left corner of the created window
		50, // The y-coordinate of the upper left corner of the created window
		1200, // Width of window
		600, // Height of window
		0
	);

	if (!mWindow)
	{
		SDL_Log("Unable to create window %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED
	);

	return true;

};

void Game::RunLoop()
{
	while (is_running)
	{
		ProcessInput();
		UpdateWorld();
		GenerateOutput();
	}
};

void Game::ProcessInput()
{
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

	player_movement = 0;

	if (state[SDL_SCANCODE_W])
	{
		player_movement--;
	}
	if (state[SDL_SCANCODE_S])
	{
		player_movement++;
	}
	std::cout << "Needed ticks: " << last_projectile_ticks + projectile_cooldown_seconds * 1000 << std::endl;
	if (state[SDL_SCANCODE_SPACE] && (ticks_passed > (last_projectile_ticks + projectile_cooldown_seconds * 1000)))
	{
		std::cout << "Generating bullet.........................." << std::endl;
		for (int i = 0; i < sizeof(projectiles); i++)
		{
			if (!(projectiles[i].is_active))
			{
 				projectiles[i].is_active = true;
				projectiles[i].position.x = player_pos.x;
				projectiles[i].initial_position.x = player_pos.x;
				projectiles[i].position.y = player_pos.y;
				projectiles[i].initial_position.y = player_pos.y;
				projectiles[i].velocity.x = player_projectile_speed;
				projectiles[i].velocity.y = 0;
				projectiles[i].range = player_projectile_range;
				last_projectile_ticks = ticks_passed;
				break;
			}
		}
	}
};

void Game::UpdateWorld()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_passed + 16)); // Wait until 16 ms (60fps) has elapsed

	float delta_time = (SDL_GetTicks() - ticks_passed) / 1000.0f;

	if (delta_time > 0.05)
	{
		delta_time = 0.05;
	}

	ticks_passed = SDL_GetTicks();

	player_pos.y += player_movement;

	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (projectiles[i].is_active)
		{
			projectiles[i].Update();
		}
	}
	
	for (int i = 0; i < 100; i++)
	{
		rows[i].Update();
	}
};

void Game::GenerateOutput()
{

	std::cout << "Ticks: " << ticks_passed << std::endl;

	// Sets draw colour to dark blueish
	SDL_SetRenderDrawColor(
		mRenderer,
		0,
		0,
		100,
		255
	);

	// Sets back buffer to current draw colour
	SDL_RenderClear(
		mRenderer
	);

	// Set colour to white
	SDL_SetRenderDrawColor(
		mRenderer,
		255,
		255,
		255,
		255
	);

	// Draw player
	SDL_Rect player
	{
		static_cast<int> (player_pos.x - 10),
		static_cast<int> (player_pos.y - 10),
		20,
		20
	};

	SDL_RenderFillRect(
		mRenderer,
		&player
	);

	PrintBullets();

	std::cout << "Player x: " << static_cast<int> (player_pos.x - 10) << std::endl;
	std::cout << "Player y: " << static_cast<int> (player_pos.y - 10) << std::endl;

	// Switch back buffer with screen
	SDL_RenderPresent(
		mRenderer
	);
}

void Game::PrintBullets()
{
	for (Projectile projectile : projectiles)
	{
		if (projectile.is_active)
		{
			SDL_Rect bullet
			{
				static_cast<int> (projectile.position.x - projectile.size / 2),
				static_cast<int> (projectile.position.y - projectile.size / 2),
				projectile.size,
				projectile.size
			};
			SDL_RenderFillRect(
				mRenderer,
				&bullet
			);
		}
	}
}

void Game::Terminate()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
