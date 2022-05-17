#pragma once

#include "types.h"
#include "shader.h"
#include <glad/glad.h>
#include <vector>
#include <array>
#include <memory>

class GlObj
{
public:
	GlObj(
		std::vector<std::vector<vec3>> const &vertex_data,
		std::vector<unsigned int> const &indices);
	~GlObj();
	GLuint get_vao() const { return vao; };
	void render(std::shared_ptr<Shader> const &shader) const;

private:
	GLuint vbo;
	GLuint vao;
	GLuint ebo;
	GLsizei const ebo_len;
};
