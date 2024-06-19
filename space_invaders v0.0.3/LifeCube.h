#pragma once

#include "Structs.h"

class LifeCube
{

public:

	xy_vector position;
	xy_vector velocity_of_created_bullets;
	xy_vector position_of_created_bullets;

	void Activate(float stated_health);

	bool IsDestroyed(float damage);

	float initial_health;
	float current_health;

	bool is_invader;
	bool is_player;
	bool is_active;

	bool is_shooting;
};

