#pragma once
#include "SDL.h"
#include <string>

#include "LifeCube.h"
#include "Invader.h"
#include "Bullet.h"

class Game
{
public:

	Game();
	
	bool Initialise();

	void RunLoop();

	void Terminate();

private:
	// Size of cubes
	int CUBE_SIZE;

	// Thickness & colour of health bars
	int HEALTH_BAR_THICKNESS;
	Colour HEALTH_BAR_COLOUR;

	// Colour of background
	Colour BACKGROUND_COLOUR;

	// SDL Window object
	SDL_Window* window;

	// Renderer to draw graphics onto window
	SDL_Renderer* renderer;

	// How many ticks the game has been running for ( framerate control )
	int ticks_passed;

	// Should the game keep running? When turned false, the game loop ends and termination begins.
	bool is_running;

	// Input helper function
	bool HandleInputs();

	// Input variables
	bool w_was_pressed;
	bool a_was_pressed;
	bool s_was_pressed;
	bool d_was_pressed;
	bool space_was_pressed;

	// Is the game currently in the menu?
	bool in_menu;

	// Which screen?
	int menu_tree;

	// What is printed on menu
	std::string menu_options[4];

	// Which menu option is currently selected
	int selected_menu;

	// Menu functions
	void UpdateMenu();
	void DrawMenu();

	// Game functions
	void UpdateGame();
	void DrawGame();

	// Player cube
	LifeCube player;

	// Initialise player cube
	void InitialisePlayer();

	// Default colours
	Colour WHITE;

	// Coordinate limits, player cannot move outside this box
	int BOUNDS_TOP;
	int BOUNDS_BOTTOM;
	int BOUNDS_LEFT;
	int BOUNDS_RIGHT;

	// Projectile Speed (doubled for player)
	float projectile_speed;
	int last_shot_tick;
	int player_gun_cooldown_seconds;

	Row debug_row;

	int ROW_AMOUNT = 1;
	Row rows[50];

	Bullet bullets[200];
	Bullet bullets_to_activate[5];
	int BULLET_SIZE;
	int BULLET_RANGE;

	void AddBulletToList
	(
		xy_vector position,
		xy_vector velocity,
		bool from_player
	);

	void ActivateBullets();

	void DetectHits();
};

