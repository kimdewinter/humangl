#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Env
{
public:
	Env();
	~Env();
	void process_input();
	bool should_window_close() const { return glfwWindowShouldClose(this->window); };
	void swap_buffers() const { glfwSwapBuffers(this->window); };
	void poll_events() const { glfwPollEvents(); };

private:
	GLFWwindow *window;
};
