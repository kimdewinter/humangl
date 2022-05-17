#include "renderer.h"
#include "main.h"
#include "model.h"
#include <map>
#include <thread> // Possibly only needed for test-sleeps during development; remove later

namespace Renderer
{
	void render(Env const &env, std::map<std::string, Model *> const &renderables)
	{
		PRINT_OUT("Rendering.");
		std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Simulates rendering

		glClearColor(CLEAR_COLOR_R, CLEAR_COLOR_G, CLEAR_COLOR_B, CLEAR_COLOR_A);
		glClear(GL_COLOR_BUFFER_BIT);

		for (std::pair<std::string, Model *> const item : renderables)
		{
			if (item.second)
			{
				item.second->render();
			}
		}

		env.swap_buffers();
		env.poll_events();
	}
}
