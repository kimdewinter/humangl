#include "env.h"

InputHandler::InputHandler()
{
	this->keys = {
		new Unrepeatable(GLFW_KEY_ESCAPE, [&]()
						 { glfwSetWindowShouldClose(this->window, true); }),
	};
}

InputHandler::~InputHandler()
{
	for (auto key : this->keys)
		delete key;
}

void InputHandler::handle_input(GLFWwindow *window, World *world)
{
	this->window = window;
	this->world = world;

	for (auto key : this->keys)
		key->handle_input(window);

	this->window = NULL;
	this->world = NULL;
}

bool InputHandler::Key::is_currently_pressed(GLFWwindow *window) const
{
	return glfwGetKey(window, this->key) == GLFW_PRESS;
}

void InputHandler::Repeatable::handle_input(GLFWwindow *window)
{
	if (this->is_currently_pressed(window))
		this->action();
}

void InputHandler::Unrepeatable::handle_input(GLFWwindow *window)
{
	if (is_currently_pressed(window))
	{
		if (!this->previously_pressed)
		{
			this->action();
			this->previously_pressed = true;
		}
	}
	else
	{
		this->previously_pressed = false;
	}
}
