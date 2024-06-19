#pragma once

#include "Invader.h"

class Row
{
public:
	float x;
	float y;
	float row_speed;
	float width;
	bool invaded;
	Invader invaders[50];

	// Update row
	void Update();
};