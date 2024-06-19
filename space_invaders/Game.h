#pragma once

#include <SDL.h>
#include "Structs.h"
#include "projectile.h"

class Game
{

public:

	Game();

	bool Initialize();

	void RunLoop();

	void Terminate();

private:

	void ProcessInput();

	void UpdateWorld();

	void GenerateOutput();

	void PrintBullets();

	// SDL Window object
	SDL_Window* mWindow;

	// Renderer to draw graphics onto window
	SDL_Renderer* mRenderer;

	// How many ticks the game has been running for ( framerate control )
	int ticks_passed;

	// Should the game keep running? When turned false, the game loop ends and termination begins.
	bool is_running;

	// Posotion of player
	xy_vector player_pos;

	// Movement in player, - is up, + is down.
	int player_movement;

	// Projectiles
	const int MAX_PROJECTILES = 100;

	Projectile projectiles[100];

	int projectile_cooldown_seconds;
	int last_projectile_ticks;
	int player_projectile_speed;
	int player_projectile_range;

	// Enemy rows


};

