#pragma once

#include "Row.h"

class InvaderStructure
{
public:

	void Clear();

	float health_of_cubes;

	void InitialiseCubeHealth();

	/*
	The number of active rows in the structure.The game only loops through the
	first rows, which frees up power to simulte projectiles.

	Rows in the structure are spaced (row[0]) (space_between_rows) (row[1])
	and so on.
	*/

	int rows_in_structure;
	int space_between_rows;

	Row rows[12];

	xy_vector position_of_upper_left_cube;
	
	void Update(float progression);

	float y_pixels_per_frame;
	bool y_is_increasing;
	float initial_x;

	bool is_active;

	int height_in_pixels;
	int width_in_pixels;
};

