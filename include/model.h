#pragma once

#include <glad/glad.h>
#include <forward_list>
#include "types.h"
#include <string>

class Model
{
public:
	Model(
		const std::string name,
		std::forward_list<Model *> children,
		const vec3 position,
		const vec3 orientation,
		const vec3 scaling,
		vec3 color);
	~Model();
	void render(); // TO IMPLEMENT

private:
	std::string name;
	std::forward_list<Model *> children;

	GLuint vbo;
	GLuint vao;
	GLuint ebo;

	vec3 position;
	vec3 orientation;
	vec3 scaling;

	vec3 color;
};
