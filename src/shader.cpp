#include "shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace
{
	/// Returns one continuous string of all bytes of a whole file
	std::string const f_to_str(const char *file_path)
	{
		std::string source;
		std::ifstream file;

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

Shader::Shader(const char *vert_path, const char *frag_path)
try
{
	std::string vert_src = f_to_str(vert_path);
	std::string frag_src = f_to_str(frag_path);
	// TO DO: FINISH THIS
	// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader.h
}
catch (char const *const msg)
{
	throw msg;
}