#pragma once

#include "types.h"
#include <iostream>
#include <glad/glad.h>

/// OpenGL Shader program. Can use for multiple Models by using a std::shared_ptr.
class Shader
{
public:
	Shader(std::string const &vert_path, std::string const &frag_path);
	~Shader();
	GLuint get_id() const;
	void use() const;
	void setMat4(std::string const &uniform_name, mat4 const &mat4) const;

private:
	GLuint id; // ID of final shader program
};
