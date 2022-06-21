#include "main.h"
#include "env.h"
#include "model.h"
#include "shader.h"
#include "world.h"
#include <chrono>
#include <thread> // Possibly only needed for test-sleeps during development; remove later
#include <iostream>

namespace
{
	void update()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulates updating of game state
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
		env.poll_events();
	}
}

int main()
{
	Env env;
	World world;
	populate_world(world);

	// env.select_model(game_obj.find("skelly")->second);
	/*
		env.select_model(game_obj.find("skelly")->second->find_child("torso"));
		auto skelly_models = game_obj.find("skelly")->second->get_all_models();
		for (auto child : skelly_models)
		{
			PRINT_OUT(child->get_name());
		}
		return EXIT_SUCCESS;
	*/

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

		env.process_input();

		while (lag >= ns_per_update)
		{
			update();
			lag -= ns_per_update;
		}

		render(env, world);
	}

	PRINT_OUT("Program complete.");
	return EXIT_SUCCESS;
}
