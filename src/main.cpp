#include "main.h"
#include "env.h"
#include "renderer.h"
#include "model.h"
#include "skelly.h"
#include <chrono>
#include <thread> // Possibly only needed for test-sleeps during development; remove later
#include <iostream>

static void update()
{
	std::cout << "Updating game state." << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulates updating of game state
}

static void process_input(Env *env)
{
	std::cout << "Processing input." << std::endl;
	env->process_input();
	std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulates processing of input
}

static void render(Env *env)
{
	std::cout << "Rendering." << std::endl;
	Renderer::render(env);
	std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Simulates rendering
}

int main()
{
	Env env;
	// std::map<std::string, Model *> game_obj = Skelly::create_skelly();

	// Game loop
	using namespace std::chrono;
	const nanoseconds ns_per_update = duration_cast<nanoseconds>(milliseconds(MS_PER_UPDATE));

	time_point previous = steady_clock::now();
	nanoseconds lag = nanoseconds(0);
	while (!env.should_window_close())
	{
		time_point current = steady_clock::now();
		nanoseconds elapsed = current - previous;
		previous = current;
		lag += elapsed;

		process_input(&env);

		while (lag >= ns_per_update)
		{
			update();
			lag -= ns_per_update;
		}

		render(&env);
	}

	std::cout << "Program complete." << std::endl;
	return EXIT_SUCCESS;
}
