#pragma once

#include "types.h"
#include <iostream>
#include <glad/glad.h>

class Shader
{
public:
	Shader(std::string const &vert_path, std::string const &frag_path);
	~Shader();
	GLuint get_id() const { return id; };
	void use() const { glUseProgram(this->id); };
	void setMat4(std::string const &uniform_name, mat4 const &mat4) const;

private:
	GLuint id; // ID of final shader program
};
