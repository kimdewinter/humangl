#include "renderer.h"

namespace Renderer
{
	void render(Env *env)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		env->swap_buffers();
		env->poll_events();
	}
}
