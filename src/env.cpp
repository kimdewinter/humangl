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

	glClearColor(CLEAR_COLOR_R, CLEAR_COLOR_G, CLEAR_COLOR_B, CLEAR_COLOR_A);
}

Env::~Env()
{
	glfwDestroyWindow(this->window);
	this->window = NULL;
	glfwTerminate();
}

void Env::process_input(World &world)
{
	// Anonymous function that checks if a key has been pressed
	std::function<bool(int)> pressed = [this](int key)
	{ return glfwGetKey(this->window, key) == GLFW_PRESS; };

	// Close window when escape is pressed
	if (pressed(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(this->window, true);

	if (std::shared_ptr<Model> selected = world.get_selected().lock())
	{
		// Check keypresses that change position
		if (pressed(GLFW_KEY_Q))
			selected->modify_position({0.0, -MOVEMENT_SPEED, 0.0});
		if (pressed(GLFW_KEY_W))
			selected->modify_position({0.0, 0.0, -MOVEMENT_SPEED});
		if (pressed(GLFW_KEY_E))
			selected->modify_position({0.0, MOVEMENT_SPEED, 0.0});
		if (pressed(GLFW_KEY_A))
			selected->modify_position({-MOVEMENT_SPEED, 0.0, 0.0});
		if (pressed(GLFW_KEY_S))
			selected->modify_position({0.0, 0.0, MOVEMENT_SPEED});
		if (pressed(GLFW_KEY_D))
			selected->modify_position({MOVEMENT_SPEED, 0.0, 0.0});
		// Check keypresses that change orientation (rotation)
		if (pressed(GLFW_KEY_R))
			selected->modify_orientation({0.0, 0.0, MOVEMENT_SPEED});
		if (pressed(GLFW_KEY_T))
			selected->modify_orientation({-MOVEMENT_SPEED, 0.0, 0.0});
		if (pressed(GLFW_KEY_Y))
			selected->modify_orientation({0.0, 0.0, -MOVEMENT_SPEED});
		if (pressed(GLFW_KEY_F))
			selected->modify_orientation({0.0, -MOVEMENT_SPEED, 0.0});
		if (pressed(GLFW_KEY_G))
			selected->modify_orientation({MOVEMENT_SPEED, 0.0, 0.0});
		if (pressed(GLFW_KEY_H))
			selected->modify_orientation({0.0, MOVEMENT_SPEED, 0.0});
		// Check keypresses that change scale
		if (pressed(GLFW_KEY_U))
			selected->modify_scale({0.0, -MOVEMENT_SPEED, 0.0});
		if (pressed(GLFW_KEY_I))
			selected->modify_scale({0.0, 0.0, MOVEMENT_SPEED});
		if (pressed(GLFW_KEY_O))
			selected->modify_scale({0.0, MOVEMENT_SPEED, 0.0});
		if (pressed(GLFW_KEY_J))
			selected->modify_scale({-MOVEMENT_SPEED, 0.0, 0.0});
		if (pressed(GLFW_KEY_K))
			selected->modify_scale({0.0, 0.0, -MOVEMENT_SPEED});
		if (pressed(GLFW_KEY_L))
			selected->modify_scale({MOVEMENT_SPEED, 0.0, 0.0});
		// Check keypresses that center/reset everything
		if (pressed(GLFW_KEY_C))
		{
			selected->reset_position();
			selected->reset_orientation();
			selected->reset_scale();
		}
#if DEBUG_MODELS == 1
		selected->debug_model_data();
#endif
	}
}
