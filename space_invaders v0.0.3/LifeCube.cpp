#include "LifeCube.h"

void LifeCube::Activate(float stated_health)
{
	is_active = true;
	is_shooting = false;
	initial_health = current_health = stated_health;
}

bool LifeCube::IsDestroyed(float damage)
{
	current_health -= damage;

	if (current_health < 0)
	{
		is_active = false;
		return true;
	}

	return false;
}
