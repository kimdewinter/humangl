#include "main.h"
#include "env.h"
#include <stdlib.h>
#include <iostream>

namespace
{
	void framebuffer_size_callback(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
}

Env::Env()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, WINDOW_RESIZABLE);
	glfwWindowHint(GLFW_SAMPLES, 8); // MSAA

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	this->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME, NULL, NULL);
	if (!window)
	{
		PRINT_OUT("GLFW window creation failed");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(this->window);
	glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, 1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		PRINT_OUT("GLAD initialization failed");
		glfwTerminate();
		return;
	}

#if DEPTH_TESTING == 1
	glEnable(GL_DEPTH_TEST);
#endif
	glEnable(GL_MULTISAMPLE); // MSAA

#if WIREFRAME_MODE == 1
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
}

Env::~Env()
{
	glfwDestroyWindow(this->window);
	this->window = NULL;
	glfwTerminate();
}

void Env::process_input()
{
	// Anonymous function that checks if a key has been pressed
	std::function<bool(int)> pressed = [this](int key)
	{ return glfwGetKey(this->window, key) == GLFW_PRESS; };

	// Anonymous function that checks if private member var "selected_model" is pointing at something
	std::function<bool()> model = [this]()
	{ return this->selected_model; };

	// Close window when escape is pressed
	if (pressed(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(this->window, true);

	if (this->selected_model)
	{
		// Check keypresses that change position
		if (pressed(GLFW_KEY_Q))
			this->selected_model->modify_position({0.0, -MOVEMENT_SPEED, 0.0});
		if (pressed(GLFW_KEY_W))
			this->selected_model->modify_position({0.0, 0.0, -MOVEMENT_SPEED});
		if (pressed(GLFW_KEY_E))
			this->selected_model->modify_position({0.0, MOVEMENT_SPEED, 0.0});
		if (pressed(GLFW_KEY_A))
			this->selected_model->modify_position({-MOVEMENT_SPEED, 0.0, 0.0});
		if (pressed(GLFW_KEY_S))
			this->selected_model->modify_position({0.0, 0.0, MOVEMENT_SPEED});
		if (pressed(GLFW_KEY_D))
			this->selected_model->modify_position({MOVEMENT_SPEED, 0.0, 0.0});
		// Check keypresses that change orientation (rotation)
		if (pressed(GLFW_KEY_R))
			this->selected_model->modify_orientation({0.0, 0.0, MOVEMENT_SPEED});
		if (pressed(GLFW_KEY_T))
			this->selected_model->modify_orientation({-MOVEMENT_SPEED, 0.0, 0.0});
		if (pressed(GLFW_KEY_Y))
			this->selected_model->modify_orientation({0.0, 0.0, -MOVEMENT_SPEED});
		if (pressed(GLFW_KEY_F))
			this->selected_model->modify_orientation({0.0, -MOVEMENT_SPEED, 0.0});
		if (pressed(GLFW_KEY_G))
			this->selected_model->modify_orientation({MOVEMENT_SPEED, 0.0, 0.0});
		if (pressed(GLFW_KEY_H))
			this->selected_model->modify_orientation({0.0, MOVEMENT_SPEED, 0.0});
		// Check keypresses that change scaling
		if (pressed(GLFW_KEY_U))
			this->selected_model->modify_scaling({0.0, -MOVEMENT_SPEED, 0.0});
		if (pressed(GLFW_KEY_I))
			this->selected_model->modify_scaling({0.0, 0.0, MOVEMENT_SPEED});
		if (pressed(GLFW_KEY_O))
			this->selected_model->modify_scaling({0.0, MOVEMENT_SPEED, 0.0});
		if (pressed(GLFW_KEY_J))
			this->selected_model->modify_scaling({-MOVEMENT_SPEED, 0.0, 0.0});
		if (pressed(GLFW_KEY_K))
			this->selected_model->modify_scaling({0.0, 0.0, -MOVEMENT_SPEED});
		if (pressed(GLFW_KEY_L))
			this->selected_model->modify_scaling({MOVEMENT_SPEED, 0.0, 0.0});
		// Check keypresses that center/reset everything
		if (pressed(GLFW_KEY_C))
		{
			this->selected_model->reset_position();
			this->selected_model->reset_orientation();
			this->selected_model->reset_scaling();
		}
#if DEBUG_MODELS == 1
		this->selected_model->print_model_data();
#endif
	}
}
