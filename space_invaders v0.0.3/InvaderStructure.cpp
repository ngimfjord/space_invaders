#include "InvaderStructure.h"

void InvaderStructure::Clear()
{
	for (int i = 0; i < 12; i++)
	{
		rows[i].Clear();
	}
	is_active = false;
}

void InvaderStructure::InitialiseCubeHealth()
{
	for (int i = 0; i < rows_in_structure; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			rows[i].invaders[j].initial_health = health_of_cubes;
			rows[i].invaders[j].current_health = health_of_cubes;
		}
	}
}

void InvaderStructure::Update(float progression)
{
	if (y_is_increasing)
	{
		position_of_upper_left_cube.y += y_pixels_per_frame;
		if (position_of_upper_left_cube.y + height_in_pixels > 550)
		{
			position_of_upper_left_cube.y = 550.0f - height_in_pixels;
			y_is_increasing = false;
		}
	} 
	else 
	{
		position_of_upper_left_cube.y -= y_pixels_per_frame;
		if (position_of_upper_left_cube.y < 50)
		{
			position_of_upper_left_cube.y = 50.0f;
			y_is_increasing = true;
		}
	}
	// Loop through the rows of the structure
	for (int i = 0; i < rows_in_structure; i++)
	{
		rows[i].position_of_top_cube = position_of_upper_left_cube;
		rows[i].position_of_top_cube.x += i*space_between_rows;
		rows[i].UpdateCubes();
	}

	position_of_upper_left_cube.x = initial_x - progression;
}
