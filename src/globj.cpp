#include <iostream>
#include "globj.h"
#include "main.h"

// Namespace for helpers of GlObj::GlObj
namespace
{
	/// Error-check vertex attribute data length, and return total number of vertices
	/// Ex: if there are two attributes, and A has 20 vertices, then B must also have 20 vertices
	size_t check_vertexattrib_len(std::vector<std::vector<vec3>> const &vecs)
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
	std::vector<vec3> const format_vertex_data(std::vector<std::vector<vec3>> const &in)
	{
		using std::string;
		using std::vector;

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
		vector<vec3> out;
		for (int vert_i = 0; vert_i < n_vertices; vert_i++)
			for (vector<vec3> const &in_i : in)
				out.push_back(in_i.at(vert_i));
		return out;
	}

	template <typename T>
	size_t sizeof_vector(typename std::vector<T> const &vec)
	{
		return sizeof(T) * vec.size();
	}
}

/// Object that hands buffering and draw calls.
/// 'vertex_data' should contain vectors with your position attributes, normal attributes, etc.
/// in the GLSL shader they correspond to "layout (location = 0)", "layout (location = 1)", etc.
/// 'indices' holds the vertex indices, so glDrawElements can be used; avoiding duplicate vertices.
GlObj::GlObj(
	std::vector<std::vector<vec3>> const &vertex_data,
	std::vector<unsigned int> const &indices) : ebo_len(indices.size())
{
	try
	{
		std::vector<vec3> formatted_vertex_data = format_vertex_data(vertex_data);

		// Generate buffers
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		// Buffer vertex data
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(
			GL_ARRAY_BUFFER,
			sizeof_vector(formatted_vertex_data),
			formatted_vertex_data.data(),
			GL_STATIC_DRAW);

		// Buffer indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			sizeof_vector(indices),
			indices.data(),
			GL_STATIC_DRAW);

		// Set position attribute, AKA "layout (location = 0)"
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
		glEnableVertexAttribArray(0);
	}
	catch (char const *const msg)
	{
		throw msg;
	}
}

GlObj::~GlObj()
{
	glDeleteVertexArrays(1, &this->vao);
	glDeleteBuffers(1, &this->vbo);
	glDeleteBuffers(1, &this->ebo);
}

/// Renders the VAO by using the given shader, setting any uniforms via an anonymous function,
/// and then calling glDrawElements()
void GlObj::render(
	std::shared_ptr<Shader> const &shader,
	std::function<void()> uniform_setter) const
{
	shader->use();
	glBindVertexArray(this->vao);
	uniform_setter();
	glDrawElements(GL_TRIANGLES, this->ebo_len, GL_UNSIGNED_INT, (void *)0);
}
