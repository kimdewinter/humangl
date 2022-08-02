#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>
#include "model.h"

/// Handles context and window creation, as well as buffer clearing, swapping,
/// event polling, input handling.
class Env
{
public:
	Env();
	~Env();
	void process_input(World &world);
	bool should_window_close() const { return glfwWindowShouldClose(this->window); };
	void clear_buffers() const { glClear(GL_COLOR_BUFFER_BIT); };
	void swap_buffers() const { glfwSwapBuffers(this->window); };
	void poll_events() const { glfwPollEvents(); };

private:
	class Key
	{
	public:
		Key(
			int const key,
			std::function<void()> action) : key(key),
											action(action){};
		void check(GLFWwindow *window);

	protected:
		int const key;
		std::function<void()> action;
		bool is_currently_pressed(GLFWwindow *window);
	};

	class Unrepeatable : public Key
	{
	public:
		void check(GLFWwindow *window);

	private:
		bool previously_pressed = false;
	};

	GLFWwindow *window;
	std::array<Key, 1> keys;

	void setup_keys();
};
