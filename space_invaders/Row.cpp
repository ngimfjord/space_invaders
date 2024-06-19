#include "Row.h"

void Row::Update()
{
	x -= row_speed;

	if (x <= 100)
	{
		invaded = true;
	}
}
