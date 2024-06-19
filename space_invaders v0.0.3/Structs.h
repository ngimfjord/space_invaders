#pragma once

#include <cstdint>

struct xy_vector
{
	float x;
	float y;
	
	void AddVectors(xy_vector vector1, xy_vector vector2);

	void AddAndChange(xy_vector other_vector);

	float Distance(xy_vector other_vector);
};

struct Colour
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;

	void Set(uint8_t new_red, uint8_t new_green, uint8_t new_blue, uint8_t new_alpha);
};