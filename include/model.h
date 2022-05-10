#pragma once

#include <glad/glad.h>
#include <forward_list>
#include "types.h"
#include <string>
#include <vector>

class Model
{
public:
	Model(
		const std::string name,
		std::forward_list<Model *> children,
		const std::vector<vec3> vertices,
		const std::vector<unsigned int> indices,
		vec3 position,
		vec3 orientation,
		vec3 scaling,
		vec3 color);
	~Model();
	void render(); // TO IMPLEMENT

private:
	const std::string name;
	std::forward_list<Model *> children;

	GLuint vbo;
	GLuint vao;
	GLuint ebo;

	vec3 position;
	vec3 orientation;
	vec3 scaling;

	vec3 color;
};
