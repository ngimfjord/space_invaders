#include "projectile.h"
#include <cmath>

Projectile::Projectile()
{
	is_active = false;
	size = 6;
}

void Projectile::Update()
{
	position.x += velocity.x;
	position.y += velocity.y;

	if (std::abs(position.x - initial_position.x) > range || std::abs(position.y - initial_position.y) > range)
	{
		is_active = false;
	}
}
