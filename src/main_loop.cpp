#include "main_loop.h"

void Updater::update(World &world, std::chrono::steady_clock::time_point const now)
{
	if (this->first_update)
	{
		this->first_update = false;
		this->last_update_timestamp = now;
		world.update(now, last_update_timestamp);
	}
	else
	{
		world.update(now, last_update_timestamp);
		this->last_update_timestamp = now;
	}
}
