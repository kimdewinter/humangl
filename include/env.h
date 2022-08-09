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
		Key(int const key, std::function<void()> const action) : key{key}, action{action} {};
		virtual void handle_input(GLFWwindow *window) = 0; // Call this for each Key to handle input
		virtual ~Key() = default;

	protected:
		int const key;
		std::function<void()> const action;
		bool is_currently_pressed(GLFWwindow *window) const;
	};

	class Repeatable : public Key
	{
	public:
		Repeatable(int const key, std::function<void()> const action) : Key{key, action} {};
		void handle_input(GLFWwindow *window);
	};

	class Unrepeatable : public Key
	{
	public:
		Unrepeatable(int const key, std::function<void()> const action) : Key{key, action} {};
		void handle_input(GLFWwindow *window);

	private:
		bool previously_pressed = false;
	};

	GLFWwindow *window;
	std::vector<Key *> keys = {
		new Repeatable(GLFW_KEY_ENTER, []()
					   { std::cout << "enter" << std::endl; }),
		new Unrepeatable(GLFW_KEY_SPACE, []()
						 { std::cout << "space" << std::endl; }),
	};
};
