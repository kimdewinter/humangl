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
	void swap_buffers() const { glfwSwapBuffers(this->window); };
	void poll_events() const { glfwPollEvents(); };
	// void select_model(Model *selectee) { this->selected_model = selectee; };

private:
	GLFWwindow *window;
	// std::map<std::string, Model *> game_objs;

	// Selector *selector = nullptr;
	// class Selector
	// {
	// public:
	// 	Selector(std::vector<Model *> models);
	// 	Model const *const get_selected() const { return *this->selected; };

	// private:
	// 	std::vector<Model *> models;
	// 	std::vector<Model *>::iterator selected = models.begin();
	// };
};
