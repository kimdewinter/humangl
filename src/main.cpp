#include "main.h"
#include "env.h"
#include "model.h"
#include "shader.h"
#include "world.h"
#include <chrono>
#include <iostream>

namespace
{
	void update()
	{
		// Placeholder for updating game logic
	}

	void populate_world(World &world)
	{
		std::shared_ptr<Shader> shader =
			std::make_shared<Shader>("resources/shader.vert", "resources/shader.frag");
		world.spawn_object("skelly", Skelly(shader));
	}

	void render(Env const &env, World &world)
	{
		env.clear_buffers();
		world.render();
		env.swap_buffers();
	}
}

int main()
{
	Env env;
	World world;
	populate_world(world);

	// Game loop
	using namespace std::chrono;
	nanoseconds const ns_per_update = duration_cast<nanoseconds>(milliseconds(MS_PER_UPDATE));

	steady_clock::time_point previous = steady_clock::now();
	nanoseconds lag = nanoseconds(0);
	while (!env.should_window_close())
	{
		steady_clock::time_point current = steady_clock::now();
		nanoseconds elapsed = current - previous;
		previous = current;
		lag += elapsed;

		env.process_input(&world);

		while (lag >= ns_per_update)
		{
			update();
			lag -= ns_per_update;
		}

		render(env, world);
		env.poll_events();
	}

	PRINT_OUT("Program complete.");
	return EXIT_SUCCESS;
}
