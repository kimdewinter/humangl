#pragma once

#include <glad/glad.h>

class Shader
{
public:
	Shader(const char *vert_path, const char *frag_path);
	~Shader();
	GLuint get_id() const { return id; };

private:
	GLuint id; // ID of final shader program
};
