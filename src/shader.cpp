#include "shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace
{
	void check_compilation_errors(GLuint const shader)
	{
		GLint success;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar info_log[1024];
			glGetShaderInfoLog(shader, 1024, NULL, info_log);
			std::cout << "ERROR:SHADER_COMPILATION_ERROR:" << std::endl
					  << info_log << std::endl;
			throw;
		}
	}

	void check_linking_errors(GLuint const shader)
	{
		GLint success;

		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR:SHADER_LINKING_ERROR:" << std::endl
					  << infoLog << std::endl;
			throw;
		}
	}

	/// Returns one continuous string of all bytes of a whole file
	std::string const f_to_str(std::string const &file_path)
	{
		std::ifstream file;
		std::string source;

		file.exceptions(std::ifstream::failbit | std::ifstream::badbit); // Make sure ifstream can throw exceptions

		try
		{
			file.open(file_path);
			std::stringstream stream;
			stream << file.rdbuf();
			file.close();
			source = stream.str();
		}
		catch (std::ifstream::failure &e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
		}
		return source;
	}
}

Shader::Shader(std::string const &vert_path, std::string const &frag_path)
try
{
	std::string vert_src = f_to_str(vert_path);
	std::string frag_src = f_to_str(frag_path);
	GLchar const *const vert_ptr = vert_src.c_str();
	GLchar const *const frag_ptr = frag_src.c_str();

	// Compile vertex shader
	unsigned int const vert_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert_id, 1, &vert_ptr, NULL);
	glCompileShader(vert_id);
	check_compilation_errors(vert_id);

	// Compile fragment shader
	unsigned int const frag_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_id, 1, &frag_ptr, NULL);
	glCompileShader(frag_id);
	check_compilation_errors(frag_id);

	// Link shaders into a shader program
	this->id = glCreateProgram();
	glAttachShader(this->id, vert_id);
	glAttachShader(this->id, frag_id);
	glLinkProgram(this->id);
	check_linking_errors(this->id);

	// Delete shaders as they're no longer necessary
	glDeleteShader(vert_id);
	glDeleteShader(frag_id);
}
catch (char const *const msg)
{
	throw msg;
}
catch (...)
{
	throw;
}

Shader::~Shader()
{
	glDeleteProgram(this->id);
}

GLuint Shader::get_id() const
{
	return this->id;
}

void Shader::use() const
{
	glUseProgram(this->id);
}

void Shader::setMat4(std::string const &uniform_name, mat4 const &mat4) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->id, uniform_name.c_str()), 1, GL_FALSE, &mat4[0]);
}
