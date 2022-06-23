#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>
#include "model.h"

class Env
{
public:
	Env();
	~Env();
	void process_input();
	bool should_window_close() const { return glfwWindowShouldClose(this->window); };
	void clear_buffers() const { glClear(GL_COLOR_BUFFER_BIT); };
	void swap_buffers() const { glfwSwapBuffers(this->window); };
	void poll_events() const { glfwPollEvents(); };

private:
	GLFWwindow *window;
};
