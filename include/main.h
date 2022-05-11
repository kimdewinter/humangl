#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define APP_NAME "humangl"
#define OPENGL_VERSION_MAJOR 4
#define OPENGL_VERSION_MINOR 1
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 900
#define WINDOW_RESIZABLE GL_FALSE
#define MS_PER_UPDATE 30

#define PRINT_OUT(str) std::cout << #str << std::endl
