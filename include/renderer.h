#pragma once

#include "env.h"
#include "model.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>

namespace Renderer
{
	void render(Env const &env, std::map<std::string, Model *> const &renderables);
}
