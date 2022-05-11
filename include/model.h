#pragma once

#include <glad/glad.h>
#include <forward_list>
#include <string>
#include <vector>
#include "types.h"
#include "globj.h"

class Model
{
public:
	Model(
		std::string const name,
		std::forward_list<Model const *const> const children,
		std::vector<std::vector<vec3 const> const> const vertices,
		std::vector<unsigned int const> const indices,
		vec3 const position,
		vec3 const orientation,
		vec3 const scaling,
		vec3 const color);
	~Model();
	void render(); // TO IMPLEMENT

private:
	std::string const name;
	std::forward_list<Model const *const> const children;

	vec3 position;
	vec3 orientation;
	vec3 scaling;

	vec3 color;

	GlObj gl_obj;
	GLuint vbo;
	GLuint vao;
	GLuint ebo;
};
