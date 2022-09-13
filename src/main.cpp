#include "main.h"
#include "env.h"
#include "model.h"
#include "shader.h"
#include "world.h"
#include "main_loop.h"
#include <chrono>
#include <iostream>
#include <execinfo.h>
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

		PRINT_OUT("Processing input.");
		env.process_input(&world);

		while (lag >= ns_per_update)
		{
			PRINT_OUT("Updating world.");
			updater.update(world, steady_clock::now());
			lag -= ns_per_update;
		}

		PRINT_OUT("Rendering.");
		render(env, world);
		env.poll_events();
	}

	PRINT_OUT("Program complete.");
	return EXIT_SUCCESS;
}
