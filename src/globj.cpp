#include <iostream>
#include "globj.h"

namespace
{
	/// Error-check vertex attribute data length, and return total number of vertices
	/// Ex: if there are two attributes, and A has 20 vertices, then B must also have 20 vertices
	size_t check_vertexattrib_len(std::vector<std::vector<vec3> const> const &vecs)
	{
		using std::vector;

		if (vecs.size() < 1 || vecs.begin()->size() < 1)
			throw "Insufficient vertex attribute data supplied.";

		if (vecs.size() == 1)
			return vecs.begin()->size(); // Only one attribute, no need to compare

		vector<vector<vec3>>::const_iterator vecs_iter = vecs.begin();
		size_t size = vecs_iter->size();
		for (vecs_iter++; vecs_iter < vecs.end(); vecs_iter++)
			if (vecs_iter->size() != size)
				throw "Dissimilar amounts of vertex data between attributes."; // Dissimilar sizes
		return size;
	}

	/// Combine the data of the various attributes into one single, contiguous vector of vertex data
	std::vector<vec3> format_vertex_data(std::vector<std::vector<vec3> const> const &in)
	{
		using std::vector, std::string;

		// Check parameter "in"
		size_t n_vertices;
		try
		{
			n_vertices = check_vertexattrib_len(in);
		}
		catch (char const *const msg)
		{
			throw msg;
		}

		// Combine the data of the various attributes into one single, contiguous vector of vertex data
		// vector<vector<vec3>>::iterator super_iter = in.begin();
		// vector<vector<vec3>::iterator> sub_iters;
		vector<vec3> out;
		for (int vert_i = 0; vert_i < n_vertices; vert_i++)
			for (vector<vec3> const &const in_i : in)
				out.push_back(in_i.at(vert_i));
		return out;
	}

	GlObj::GlObj(
		std::vector<std::vector<std::array<GLfloat, 3>> const> const vertex_data,
		std::vector<unsigned int> const indices) : vertex_data(vertex_data),
												   indices(indices)
	{
		// glGenVertexArrays(1, &vao);
		// glGenBuffers(1, &vbo);
		// glGenBuffers(1, &ebo);

		// glBindVertexArray(vao);

		// glBindBuffer(GL_ARRAY_BUFFER, vbo);
		// glBufferData(GL_ARRAY_BUFER, sizeof()) FINISH THIS
	}
}

GLuint GlObj::get_vao() const
{
	return vao;
}
