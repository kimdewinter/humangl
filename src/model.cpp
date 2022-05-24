#include "model.h"
#include "main.h"
#include <cmath>

namespace
{
	void set_uniform_vec3(const GLuint shader_id, std::string const uniform_name, vec3 const &value)
	{
		glUniform3f(
			glGetUniformLocation(shader_id, uniform_name.c_str()),
			value[0],
			value[1],
			value[2]);
	}

	void set_uniform_vec4(const GLuint shader_id, std::string const uniform_name, vec4 const &value)
	{
		glUniform4f(
			glGetUniformLocation(shader_id, uniform_name.c_str()),
			value[0],
			value[1],
			value[2],
			value[3]);
	}

	void set_uniform_mat4(const GLuint shader_id, std::string const uniform_name, mat4 const &value)
	{
		glUniformMatrix4fv(
			glGetUniformLocation(shader_id, uniform_name.c_str()),
			1,
			GL_FALSE,
			value.data());
	}

	GLfloat degrees_to_radians(GLfloat const degrees)
	{
		return degrees * (M_PI / 180);
	}
}

Model::Model(
	std::string const name,
	std::forward_list<Model *> const children,
	std::vector<std::vector<vec3>> const vertices,
	std::vector<unsigned int> const indices,
	std::shared_ptr<Shader> const shader,
	vec3 const position,
	vec3 const orientation,
	vec3 const scaling,
	vec4 const color)
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
	this->gl_obj.render(
		this->shader,
		[&]()
		{
			GLuint id = this->shader->get_id();
			set_uniform_mat4(
				id,
				"position",
				get_translation_mat4(this->position[0], this->position[1], this->position[2]));
			set_uniform_mat4(
				id,
				"orientation",
				get_orientation_mat4(this->orientation[0], this->orientation[1], this->orientation[2]));
			set_uniform_mat4(
				id,
				"scaling",
				get_scaling_mat4(this->scaling[0], this->scaling[1], this->scaling[2]));
			set_uniform_mat4(
				id,
				"projection",
				get_projection_mat4(
					degrees_to_radians(FIELD_OF_VIEW),
					WINDOW_WIDTH / WINDOW_HEIGHT,
					PROJECTION_NEAR,
					PROJECTION_FAR));
			set_uniform_vec4(id, "color_in", this->color);
		});

	for (Model *child : this->children)
	{
		child->render();
	}
}
