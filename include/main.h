#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define APP_NAME "humangl"
#define OPENGL_VERSION_MAJOR 4
#define OPENGL_VERSION_MINOR 1
#define DEPTH_TESTING 0
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 900
#define WINDOW_RESIZABLE GL_FALSE
#define MS_PER_UPDATE 30
#define CLEAR_COLOR_R 0.2f // Red
#define CLEAR_COLOR_G 0.3f // Green
#define CLEAR_COLOR_B 0.3f // Blue
#define CLEAR_COLOR_A 1.0f // Alpha

#define PRINT_OUT(str) std::cout << str << std::endl
