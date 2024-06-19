#pragma once
#include "Structs.h"

class Bullet
{
public:
	bool is_active;

	bool can_hit_player;
	bool can_hit_invaders;

	int range;

	xy_vector position;
	float travel_distance;

	xy_vector velocity;

	void Update();
};

