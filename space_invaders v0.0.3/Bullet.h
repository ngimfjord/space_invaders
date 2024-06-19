#pragma once

#include "Structs.h"

class Bullet
{

public:
	Bullet();

	bool is_active;

	xy_vector initial_position;
	xy_vector position;
	xy_vector velocity;

	bool can_hit_player;
	bool can_hit_invaders;
	
	void UpdatePosition();

};

