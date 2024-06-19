#include <cmath>

#include "Structs.h"

void xy_vector::AddVectors(xy_vector vector1, xy_vector vector2)
{
	x = vector1.x + vector2.x;
	y = vector1.y + vector2.y;
}

void xy_vector::AddAndChange(xy_vector other_vector)
{
	x += other_vector.x;
	y += other_vector.y;
}

float xy_vector::Distance(xy_vector other_vector)
{
	float distance = 0.0f;

	distance += std::abs(x - other_vector.x);
	distance += std::abs(y - other_vector.y);

	return distance;
}

void Colour::Set(uint8_t new_red, uint8_t new_green, uint8_t new_blue, uint8_t new_alpha)
{
	red = new_red;
	green = new_green;
	blue = new_blue;
	alpha = new_alpha;
}
