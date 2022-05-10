#pragma once

#include <glad/glad.h>
#include <vector>

/// X, Y, Z
typedef std::array<GLfloat, 3> vec3;

/// X, Y, Z, W
typedef std::array<GLfloat, 4> vec4;

/// Column-first 4x4 float matrix
typedef std::array<GLfloat, 16> mat4;

class GlObj
{
public:
	GlObj(
		std::vector<std::vector<vec3> const> const vertex_data,
		std::vector<unsigned int> const indices);
	~GlObj();
	GLuint get_vao() const;
	void render() const;

private:
	std::vector<vec3> vertex_data; // vertices, normals, etc.
	std::vector<unsigned int> const indices;

	GLuint vbo;
	GLuint vao;
	GLuint ebo;
};
