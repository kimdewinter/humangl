#pragma once

#include "types.h"
#include <glad/glad.h>
#include <vector>
#include <array>

class GlObj
{
public:
	GlObj(
		std::vector<std::vector<vec3>> const &vertex_data,
		std::vector<unsigned int> const &indices);
	~GlObj();
	GLuint get_vao() const { return vao; };
	void render() const;

private:
	GLuint vbo;
	GLuint vao;
	GLuint ebo;
};
