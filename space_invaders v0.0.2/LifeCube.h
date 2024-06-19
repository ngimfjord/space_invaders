#pragma once
#include "Structs.h"

class LifeCube
{

public:

	// Is the cube currently in use and to be rendered?
	bool is_active = false;

	// Function that returns true if the cube was destroyed when hit.
	bool IsDestroyedFromHit(float recievec_damage);

	// Is the cube shooting?
	bool is_shooting;

	// What velocity does its bullets have?
	xy_vector bullet_velocity;

	// Hitpoints
	float hitpoints;
	float total_hitpoints;
	float health_percentage;

	// Position x & y
	xy_vector position;

	// Colour
	Colour colour;
};