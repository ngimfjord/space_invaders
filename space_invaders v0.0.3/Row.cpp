#include "Row.h"

void Row::Clear()
{
	for (int i = 0; i < 10; i++)
	{
		invaders[i].is_active = false;
		invaders[i].is_invader = true;
		invaders[i].is_player = false;

		invaders[i].velocity_of_created_bullets.x = -4;
		invaders[i].velocity_of_created_bullets.y = 0;
	}
	is_active = false;
}

void Row::UpdateCubes()
{
	for (int i = 0; i < 10; i++)
	{
		invaders[i].position = position_of_top_cube;
		invaders[i].position.y += i * 40;
	}
}
