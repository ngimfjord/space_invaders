#include "Invader.h"

Invader::Invader()
{
	life_cube.is_active = false;

	life_cube.colour.r = 120;
	life_cube.colour.b = 30;
	life_cube.colour.g = 30;
	life_cube.colour.a = 255;

	life_cube.health_percentage = 1.0f;
};

void Invader::Activate(int order, xy_vector bullet_velocity)
{
	offset = order * 40;
	life_cube.is_active = true;
	life_cube.total_hitpoints = 8;
	life_cube.hitpoints = life_cube.total_hitpoints;
	life_cube.health_percentage = 1;
	life_cube.is_shooting = false;
	life_cube.bullet_velocity = bullet_velocity;
};

void Invader::Update(xy_vector row_position)
{
	life_cube.position.x = row_position.x;
	life_cube.position.y = row_position.y + offset;
};

Row::Row()
{
	bullet_velocity.y = 0;
	bullet_velocity.x = -2;
	for (int i = 0; i < 10; i++)
	{
		invaders[i].Activate(i, bullet_velocity);
	}
	is_active = true;
	direction = 1;
	pixel_height = 40*9; // Width from top cube centre to bottom cube cente.
	is_generating_bullet = false;
}

void Row::Update(float invasion_speed)
{
	position.x -= invasion_speed;
	
	position.y += direction;

	if (position.y < 50)
	{
		position.y = 50;
		direction = 1;
	}	
	if ((position.y + pixel_height) > 550)
	{
		position.y = 550 - pixel_height;
		direction = -1;
	}

	for (int i = 0; i < 10; i++)
	{
		if (invaders[i].life_cube.is_active)
		{
			invaders[i].Update(position);
		}
	}

	// Enemy fire generator

	// Creates random number between 0 and 1999
	int random_number = rand() % 2000;

	for (int i = 0; (i < 10) && (random_number < 10); i++)
	{
		if ((random_number == i) && (invaders[i].life_cube.is_active))
		{
			invaders[i].life_cube.is_shooting = true;
			is_generating_bullet = true;
		}
	}
}
