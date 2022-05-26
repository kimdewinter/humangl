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
		PRINT_OUT("Updating game state.");
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulates updating of game state
	}

	void process_input(Env *env)
	{
		PRINT_OUT("Processing input.");
		env->process_input();
	}

	std::map<std::string, Model *> create_game_objects()
	{
		std::shared_ptr<Shader> shader =
			std::make_shared<Shader>("resources/shader.vert", "resources/shader.frag");

		return std::map<std::string, Model *>{
			{"skelly", Skelly::create_skelly(shader)},
		};
	}
}

int main()
{
	Env env;
	std::map<std::string, Model *> game_obj = create_game_objects();
	env.select_model(game_obj.find("skelly")->second);

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

		process_input(&env);

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
