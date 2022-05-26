#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "model.h"

class Env
{
public:
	Env();
	~Env();
	void process_input();
	bool should_window_close() const { return glfwWindowShouldClose(this->window); };
	void swap_buffers() const { glfwSwapBuffers(this->window); };
	void poll_events() const { glfwPollEvents(); };
	void select_model(Model *selectee) { this->selected_model = selectee; };

private:
	GLFWwindow *window;
	Model *selected_model = NULL;
};
