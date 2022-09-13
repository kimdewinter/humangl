#pragma once

#include "world.h"

class Updater
{
public:
	void update(World &world, std::chrono::steady_clock::time_point const now);

private:
	bool first_update = true;
	std::chrono::steady_clock::time_point last_update_timestamp;
};
