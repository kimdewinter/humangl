#include "model.h"

Model::Model(
	const std::string name,
	std::forward_list<Model *> children,
	const std::vector<vec3> vertices,
	const std::vector<unsigned int> indices,
	const vec3 position,
	const vec3 orientation,
	const vec3 scaling,
	const vec3 color) : name(name),
						children(children),
						vertices(vertices),
						indices(indices),
						position(position),
						orientation(orientation),
						scaling(scaling),
						color(color)
{
	// TO DO: set up vbo, vao, ebo, etc
}

Model::~Model()
{
	std::forward_list<Model *>::iterator iter;

	for (iter = this->children.begin(); iter != this->children.end(); iter++)
	{
		delete *iter;
	}

	// ADD LATER: deletion of vbo, vao, ebo, etc
};
