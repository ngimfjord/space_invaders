#pragma once

#include "LifeCube.h"

class Row
{
public:

	void Clear();

	void UpdateCubes();

	LifeCube invaders[10];

	xy_vector position_of_top_cube;

	bool is_active;
	bool is_going_up;
	bool is_going_down;
};

