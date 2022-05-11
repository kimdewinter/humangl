#pragma once

#include <glad/glad.h>
#include <vector>
#include <array>

/// X, Y, Z
#define SIZE_VEC3 sizeof(GLfloat) * 3
typedef std::array<GLfloat, 3> vec3;

/// X, Y, Z, W
#define SIZE_VEC4 sizeof(GLfloat) * 4
typedef std::array<GLfloat, 4> vec4;

/// Column-first 4x4 float matrix
#define SIZE_MAT4 sizeof(GLfloat) * 16
typedef std::array<GLfloat, 16> mat4;

class GlObj
{
public:
	GlObj(
		std::vector<std::vector<vec3 const> const> const &vertex_data,
		std::vector<unsigned int const> const &indices);
	~GlObj();
	GLuint get_vao() const;
	// void render() const;

private:
	std::vector<vec3> const vertex_data; // vertices, normals, etc.
	std::vector<unsigned int const> const indices;

	GLuint vbo;
	GLuint vao;
	GLuint ebo;
};
