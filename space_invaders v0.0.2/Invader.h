#pragma once
#include "LifeCube.h"
#include "Structs.h"
#include <ctime>
#include <cstdlib>

class Invader
{
public:
	// Initialize variable
	Invader();

	void Activate(int order, xy_vector bullet_velocity);

	int offset;

	LifeCube life_cube;

	void Update(xy_vector row_position);
};

class Row
{
public:
	Row();

	xy_vector bullet_velocity;

	void Update(float invasion_speed);

	void RandomShoot();

	xy_vector position;
	Invader invaders[10];

	// Is one of the cubes in the row currently generating a bullet?
	bool is_generating_bullet;

	int pixel_height;
	bool is_active;

	// - for up, + for down
	int direction;
private:
};

