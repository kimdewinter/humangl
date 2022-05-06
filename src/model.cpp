#include "model.h"

Model::Model(
	const std::string name,
	std::forward_list<Model *> children,
	const vec3 position,
	const vec3 orientation,
	const vec3 scaling,
	vec3 color) : name(name),
				  children(children),
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
