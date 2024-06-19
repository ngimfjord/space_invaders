#pragma once
#include <cstdint>

struct xy_vector 
{
	// x & y vector for position & velocities
	float x;
	float y;
};

struct Colour
{
	// 8bit colour code
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};