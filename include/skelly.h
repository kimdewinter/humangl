#pragma once
#include "model.h"
#include "types.h"

namespace Skelly
{
	/// Hardcoded constructor of the root Model, with it's children already attached
	std::shared_ptr<Model> create_skelly(std::shared_ptr<Shader> const shader);

	/// Hardcoded constructors of animations
	std::shared_ptr<Animation> create_animation_walk();
	std::shared_ptr<Animation> create_animation_jump();
}
