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

void Env::process_input(World *world)
{
	this->input_handler.handle_input(this->window, world);
}

bool Env::should_window_close() const
{
	return glfwWindowShouldClose(this->window);
}

void Env::clear_buffers() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Env::swap_buffers() const
{
	glfwSwapBuffers(this->window);
}

void Env::poll_events() const
{
	glfwPollEvents();
}
