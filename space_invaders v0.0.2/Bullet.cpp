#include "Bullet.h"
#include <cmath>

void Bullet::Update()
{
	position.x += velocity.x;
	position.y += velocity.y;
	travel_distance += velocity.x;
	travel_distance += velocity.y;

	if (travel_distance > range)
	{
		is_active = false;
	}
};