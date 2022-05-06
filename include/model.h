#pragma once

#include <glad/glad.h>
#include "types.h"

class Model
{
public:
	Model();
	~Model();

private:
	GLuint vbo;
	GLuint vao;
	GLuint ebo;

	vec3 pos;
	vec3 orientation;
	vec3 scale;

	vec3 color;
};
