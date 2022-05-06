#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Env
{
public:
	Env();
	~Env();
	void process_input();
	bool should_window_close() { return glfwWindowShouldClose(this->window); };

private:
	GLFWwindow *window;
};
