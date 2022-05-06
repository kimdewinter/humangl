#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>

/// X, Y, Z
typedef std::array<GLfloat, 3> vec3;

/// X, Y, Z, W
typedef std::array<GLfloat, 4> vec4;

/// Column-first 4x4 float matrix
typedef std::array<GLfloat, 16> mat4;
