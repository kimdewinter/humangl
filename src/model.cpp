#include "model.h"
#include "main.h"

Model::Model(
	std::string const name,
	std::forward_list<Model *> const children,
	std::vector<std::vector<vec3>> const vertices,
	std::vector<unsigned int> const indices,
	std::shared_ptr<Shader> const shader,
	vec3 const position,
	vec3 const orientation,
	vec3 const scaling,
	vec3 const color)
try : name(name),
	children(children),
	shader(shader),
	position(position),
	orientation(orientation),
	scaling(scaling),
	color(color),
	gl_obj(GlObj(vertices, indices))
{
}
catch (char const *const msg)
{
	PRINT_OUT(msg);
}

Model::~Model()
{
	for (Model *child : this->children)
		delete child;
};

void Model::render() const
{
	// TO DO: prepare matrices and such to be send to the render call and children

	this->gl_obj.render(this->shader);

	for (Model *child : this->children)
	{
		child->render();
	}
}
