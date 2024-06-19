#include "LifeCube.h"

bool LifeCube::IsDestroyedFromHit(float damage)
{
	hitpoints -= damage;
	health_percentage = hitpoints / total_hitpoints;
	if (hitpoints < 0)
	{
		is_active = false;
		return true;
	}
}
