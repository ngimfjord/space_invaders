#pragma once

#include "SDL.h"

#include "InvaderStructure.h"
#include "Bullet.h"

class Game
{

public:
	// Game object creator
	Game();

	// Level Initialiser
	bool InitialiseLevel(int n);

	// Initialises the game, sets up SDL.
	bool Initialise();

	// Runs the game until it is terminated. Returns score.
	int RunLoop();

	// Terminates SDL, closes the window.
	void Terminate();

	// Did the player win?
	bool has_won;

private:

	// Level initialisation

	/*
	Structures are spaced as (invader_structures[0]) (space_between_structures[1] pixels) (invader_structures[2])
	and so on. The game allows 100 rows, 1 row for the player, and 99 rows for the
	invaders.
	*/

	// Helper function for InitialiseLevel
	void SetPositions();

	// Helper functions for RunLoop
	void ControlFramerate();
	void ProcessInput();
	void UpdateGame();
	void DrawGame();

	// Helper functions for UpdateGame
	void UpdatePlayer();
	void UpdateInvaders();
	void UpdateBullets();
	void CheckBulletCollissions();
	void CheckLosingConditions();

	// Helper functions for DrawGame
	void SetDrawingColour(Colour colour);
	void DrawBackground();
	void DrawLifeCubes();
	void DrawBullets();

	// Bullet creator
	void CreateBullet(xy_vector position, xy_vector velocity, bool can_hit_player, bool can_hit_invaders);

	// Window and Renderer for SDL2 graphics
	SDL_Window* window;
	SDL_Renderer* renderer;

	/*
	Ticks (milliseconds) passed since the game started. This number is both used
	for framerate control and time specific functions, like invaders get faster
	as more time passes.
	*/

	int ticks_passed;
	bool is_running;
	bool is_paused;

	/*
	Inputs are handled through SDL, however these are better to have as binary
	variables. 
	*/

	bool w_is_being_pressed;
	bool s_is_being_pressed;
	bool space_is_being_pressed;
	bool escape_is_being_pressed;

	float level_progression_pixels;
	float level_progression_per_frame;
	InvaderStructure invader_structures[20];
	int amount_of_structures;
	float space_between_structures[20];

	LifeCube player;
	int last_shot_ticks;
	int cooldown_ms;

	int score;

	int ticks_at_start;

	Bullet bullets[200];

	Colour background_colour;
	Colour cube_colour;
	Colour health_bar_colour;
	Colour bullet_colour;
};

