#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "env.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void handle_input(GLFWwindow *window, World *world);

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

	GLFWwindow *window = NULL; // For use by keys' functions. Set, use "action" lambda function, and unset
	World *world = NULL;	   // For use by keys' functions. Set, use "action" lambda function, and unset
	std::vector<Key *> keys;
};
