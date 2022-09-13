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
	/// Abstract class that handles the checking and remembering of input for a given key
	class Key
	{
	public:
		Key(int const key, std::function<void()> const action);
		virtual ~Key() = default;
		virtual void handle_input(GLFWwindow *window) = 0; // Call this for each Key to handle input

	protected:
		int const key;
		std::function<void()> const action;
		bool is_currently_pressed(GLFWwindow *window) const;
	};

	/// Key that acts repeatedly on press-and-hold behaviour
	class Repeatable : public Key
	{
	public:
		Repeatable(int const key, std::function<void()> const action);
		void handle_input(GLFWwindow *window);
	};

	/// Key that acts once on press-and-hold behaviour (until released and re-pressed)
	class Unrepeatable : public Key
	{
	public:
		Unrepeatable(int const key, std::function<void()> const action);
		void handle_input(GLFWwindow *window);

	private:
		bool previously_pressed = false;
	};

	std::vector<Key *> keys;
	GLFWwindow *window = NULL; // For use by keys' functions. Set, use "action" lambda function, and unset back to NULL
	World *world = NULL;	   // For use by keys' functions. Set, use "action" lambda function, and unset back to NULL
};
