#include "main.h"
#include "env.h"
#include "renderer.h"
#include "model.h"
#include "skelly.h"
#include "shader.h"
#include <chrono>
#include <thread> // Possibly only needed for test-sleeps during development; remove later
#include <iostream>

namespace
{
	void update()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulates updating of game state
	}

	std::map<std::string, Model *> create_game_objects()
	{

		return std::map<std::string, Model *>{
			{"skelly", Skelly::create_skelly(shader)},
		};
	}
}

int main()
{
	Env env;
	std::map<std::string, Model *> game_obj = create_game_objects();
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

		Renderer::render(env, game_obj);
	}

	PRINT_OUT("Program complete.");
	return EXIT_SUCCESS;
}
