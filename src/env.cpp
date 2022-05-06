#include "main.h"
#include "env.h"
#include <stdlib.h>
#include <iostream>

static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

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
		std::cout << "GLFW window creation failed" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(this->window);
	glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, 1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD initialization failed" << std::endl;
		glfwTerminate();
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE); // MSAA
}

Env::~Env()
{
	glfwDestroyWindow(this->window);
	this->window = NULL;
	glfwTerminate();
}

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Env::process_input()
{
	// Close window when escape is pressed
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(this->window, true);
}
