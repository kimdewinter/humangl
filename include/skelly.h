#pragma once
#include "model.h"
#include "types.h"

namespace CubeCreation
{
	/// Use to get a hardcoded 1x1x1 cube
	std::vector<std::vector<vec3>> get_cube_vertices();
	std::vector<unsigned int> get_cube_indices();
}

namespace SkellyCreation
{
	/// Hardcoded constructor of a skeleton
	std::shared_ptr<Model> create_torso(std::shared_ptr<Shader> const shader);
}

namespace SkellyAnimation
{
	/// Hardcoded constructor of a skeleton's animation
	std::shared_ptr<Animation> create_animation_walk();
}
