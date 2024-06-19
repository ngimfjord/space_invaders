#pragma once
#include "Structs.h"
class Projectile
{

public:

	Projectile();

	void Update();

	bool is_active;

	int range;

	// The velocity of the projectile, 
	xy_vector velocity;

	// The location of the projectile
	xy_vector initial_position;
	xy_vector position;

	int size;
};