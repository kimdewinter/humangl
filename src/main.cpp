#include "main.h"
#include "env.h"
#include <chrono>
#include <thread> // Possibly only needed for test-sleeps during development; remove later
#include <iostream>

int main()
{
	Env *env = new ::Env();

	// Game loop
	using namespace std::chrono;
	const nanoseconds ns_per_update = duration_cast<nanoseconds>(milliseconds(MS_PER_UPDATE));

	time_point previous = steady_clock::now();
	nanoseconds lag = nanoseconds(0);
	while (!env->should_window_close())
	{
		time_point current = steady_clock::now();
		nanoseconds elapsed = current - previous;
		previous = current;
		lag += elapsed;

		std::cout << "Processing input." << std::endl;
		env->process_input();
		std::this_thread::sleep_for(milliseconds(10)); // Simulates processing of input

		while (lag >= ns_per_update)
		{
			// update();
			std::cout << "Updating game state." << std::endl;
			lag -= ns_per_update;
			std::this_thread::sleep_for(milliseconds(10)); // Simulates updating of game state
		}

		// render();
		std::cout << "Rendering." << std::endl;
		std::this_thread::sleep_for(milliseconds(20)); // Simulates rendering
	}

	std::cout << "Program complete." << std::endl;
	return EXIT_SUCCESS;
}

/*
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

//FROM: https://learnopengl.com/Getting-started/Hello-Window
*/
