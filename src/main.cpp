#include "main.h"
#include "env.h"
#include "model.h"
#include "shader.h"
#include "world.h"
#include "skelly.h"
#include "main_loop.h"
#include <chrono>
#include <iostream>
#include <execinfo.h>
#include <signal.h>
#include <unistd.h>

namespace
{
	void segfault_handler(int sig)
	{
		void *array[10];
		size_t size;

		// get void*'s for all entries on the stack
		size = backtrace(array, 10);

		// print out all the frames to stderr
		fprintf(stderr, "Error: signal %d:\n", sig);
		backtrace_symbols_fd(array, size, STDERR_FILENO);
		exit(1);
	}

	// modify this function to change what objects appear in the world
	void populate_world(World &world)
	{
		std::shared_ptr<Shader> shader =
			std::make_shared<Shader>("resources/shader.vert", "resources/shader.frag");
		std::shared_ptr<Animation> skelly_walk = Skelly::create_animation_walk();
		std::shared_ptr<Animation> skelly_jump = Skelly::create_animation_jump();
		world.spawn_object(
			"skelly",
			WorldObj(
				Skelly::create_skelly(shader),
				std::map<std::string, std::shared_ptr<Animation>>{
					{"walk", skelly_walk},
					{"jump", skelly_jump},
				},
				"jump"));
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
	signal(SIGSEGV, segfault_handler); // Prints stack trace upon seg fault
	Env env;
	World world;
	populate_world(world);
	Updater updater;

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
			updater.update(world, steady_clock::now());
			lag -= ns_per_update;
		}

		render(env, world);
		env.poll_events();
	}

	return EXIT_SUCCESS;
}
