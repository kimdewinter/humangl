#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "model.h"
#include "input.h"

/// Handles context and window creation, as well as buffer clearing, swapping,
/// event polling, input handling.
class Env
{
public:
	Env();
	~Env();
	void process_input(World *world);
	bool should_window_close() const;
	void clear_buffers() const;
	void swap_buffers() const;
	void poll_events() const;

private:
	GLFWwindow *window;
	InputHandler input_handler;
};
