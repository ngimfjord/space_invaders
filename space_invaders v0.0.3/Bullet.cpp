#include "Bullet.h"

Bullet::Bullet()
{
	is_active = false;
}

void Bullet::UpdatePosition()
{
	position.AddAndChange(velocity);

	if (position.Distance(initial_position) > 1200)
	{
		is_active = false;
	}
}